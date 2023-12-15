// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ImagePublisher.h"
#include <libUtil/FileUtil.h>
#include "opencv2/opencv.hpp"
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>

#include <thread>
#include <iostream>

using namespace app;
using namespace eprosima::fastdds::dds;

ImagePublisher::ImagePublisher(std::shared_ptr<std::shared_mutex> mutexPtr, CfgPtr cfgPtr, double fps)
    : participant_(nullptr)
    , publisher_(nullptr)
    , topic_(nullptr)
    , writer_(nullptr)
    , type_(new ImagePubSubType())
    , stop_(false)
{

    cfgCam_ = cfgPtr->getCam();
    mutexPtr_ = mutexPtr;

    int height = cfgCam_.imgSz_.h;
    int width = cfgCam_.imgSz_.w;

    frame_ = cv::Mat(height, width, CV_8UC3);

    // set publisher frequency
    frequency_ = fps;

   // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
   // https://learn.microsoft.com/en-us/windows/win32/directshow/selecting-a-capture-device?redirectedfrom=MSDN
   // command to list available video and audio devices
   // ffmpeg -list_devices true -f dshow -i dummy
   //camera_ = cv::VideoCapture(0, cv::CAP_DSHOW);
   // //// Check if camera opened successfully
   // if (!camera_.isOpened()) {
   //     std::cout << "[ImagePublisher] constructor: Error opening video stream or file" << std::endl;
   // }

   // // set the camera configuration
   // // https://docs.opencv.org/3.4/d4/d15/group__videoio__flags__base.html#gaeb8dd9c89c10a5c63c139bf7c4f5704d
   // // "Effective behaviour depends from device hardware, driver and API Backend."
   // camera_.set(cv::CAP_PROP_FRAME_HEIGHT, cfgCamPtr->imgSz_.w);
   // camera_.set(cv::CAP_PROP_FRAME_WIDTH, cfgCamPtr->imgSz_.h);
   // camera_.set(cv::CAP_PROP_FPS, cfgCamPtr->fps_.getFps());
}

bool ImagePublisher::init(CfgPtr cfg, bool use_env)
{

    image_.frame_number(0);
    std::cout << "in ImagePublisher::init" << std::endl;
    DomainParticipantQos pqos = PARTICIPANT_QOS_DEFAULT;
    pqos.name("ImagePublisher");

    auto factory = DomainParticipantFactory::get_instance();

    if (factory == NULL) {
        // ... error
    }
    if (use_env)
    {
        factory->load_profiles();
        factory->get_default_participant_qos(pqos);
    }

    // https://fast-dds.docs.eprosima.com/en/latest/fastdds/transport/transport.html
    switch (cfg.get()->getTransport()) {
    case 1: {
        std::cout << "Using TCP as transport" << std::endl;
        auto tcp_transport = std::make_shared<eprosima::fastdds::rtps::TCPv4TransportDescriptor>();
        tcp_transport->add_listener_port(5000);
        tcp_transport->set_WAN_address("127.0.0.1");

        // Link the Transport Layer to the Participant.
        pqos.transport().user_transports.push_back(tcp_transport);

        break;
    }
    case 2: {
        std::cout << "Using UDP as transport" << std::endl;
        std::shared_ptr<eprosima::fastdds::rtps::UDPv4TransportDescriptor> udp_transport = std::make_shared<eprosima::fastdds::rtps::UDPv4TransportDescriptor>();
        // udp_transport->sendBufferSize = 9216;
        // udp_transport->receiveBufferSize = 9216;
        udp_transport->non_blocking_send = true;

        pqos.transport().user_transports.push_back(udp_transport);
        pqos.transport().use_builtin_transports = false;
        break;
    }
    case 3: {
        std::cout << "Using Shared memory as transport" << std::endl;
        std::shared_ptr<eprosima::fastdds::rtps::SharedMemTransportDescriptor> shm_transport = std::make_shared<eprosima::fastdds::rtps::SharedMemTransportDescriptor>();

        // Link the Transport Layer to the Participant.
        pqos.transport().user_transports.push_back(shm_transport);
        break;
    }
    default: {
        std::cout << "USING DEFAULT BEHAVIOR" << std::endl;
    }
    }

    std::cout << "attempted to create participant" << std::endl;
   
   // participant_ = (factory->get_participant_qos_from_profile(0, pqos))->;

    // Get DomainParticipant QoS from profile
    

    participant_ = factory->create_participant(0, pqos);
    
    
    std::cout << "created participant" << std::endl;

    if (participant_ == nullptr)
    {
        return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    //CREATE THE PUBLISHER
    PublisherQos pubqos = PUBLISHER_QOS_DEFAULT;

    if (use_env)
    {
        participant_->get_default_publisher_qos(pubqos);
    }

    publisher_ = participant_->create_publisher(
        pubqos,
        nullptr);

    if (publisher_ == nullptr)
    {
        return false;
    }

    //CREATE THE TOPIC
    TopicQos tqos = TOPIC_QOS_DEFAULT;

    if (use_env)
    {
        participant_->get_default_topic_qos(tqos);
    }

    topic_ = participant_->create_topic(
        "ImageTopic",
        "Image",
        tqos);

    if (topic_ == nullptr)
    {
        return false;
    }

    // CREATE THE WRITER
    DataWriterQos wqos = DATAWRITER_QOS_DEFAULT;

    if (use_env)
    {
        publisher_->get_default_datawriter_qos(wqos);
    }

    writer_ = publisher_->create_datawriter(
        topic_,
        wqos,
        &listener_);

    if (writer_ == nullptr)
    {
        return false;
    }
    return true;
}

ImagePublisher::~ImagePublisher()
{
    if (writer_ != nullptr)
    {
        publisher_->delete_datawriter(writer_);
        std::cout << "delete_datawriter." << std::endl;
    }
    if (publisher_ != nullptr)
    {
        participant_->delete_publisher(publisher_);

        std::cout << "delete_publisher." << std::endl;
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);

    std::cout << "delete_participant." << std::endl;

}

void ImagePublisher::PubListener::on_publication_matched(
        eprosima::fastdds::dds::DataWriter*,
        const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{
    if (info.current_count_change == 1)
    {
        matched_ = info.total_count;
        firstConnected_ = true;
        std::cout << "Publisher matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        matched_ = info.total_count;
        std::cout << "Publisher unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
    }
}

void ImagePublisher::runThread()
{
    const int numSamples = cfgCam_.numSamples_;

	std::cout << "sending " << numSamples << " samples at " << frequency_ << std::endl;
	for (uint32_t i = 0; i < numSamples; i++) {
        uint64_t tBeg = APP_TIME_CURRENT_NS;
		acqImgMsg();
		preparImgMsg(i);

        uint64_t tEnd = APP_TIME_CURRENT_NS;

        uint64_t dealayNanosecond = 1e9 / frequency_;

        //wait utill delay time, interval
   // std::cout << "got here" << std::endl;
        do {
            tEnd = APP_TIME_CURRENT_NS;
        } while (tEnd - tBeg <= dealayNanosecond);

		if (!publish(false, numSamples)) {
			std::cout << "unable to send sample #" << i << std::endl;
		}
   
            /*
        uint64_t dt = tEnd - tBeg;
        //  1 / (dt / 1e6) or 1e6 / dt (converting US to HZ)
        uint64_t cycles = 1e6 / dt;
   
        // https://stackoverflow.com/questions/72914414/how-to-call-a-function-in-a-certain-frequency-c
        // std::cout << "dt is " << dt << " cycles is " << cycles << " and frequency is " << frequency_ << std::endl;
        if (cycles > frequency_) {
            // std::cout << "Slow down! cycles is " << cycles << " and frequency is " << frequency_ << std::endl;
            // if message sent too fast, wait for this many nanoseconds to send the next message
           
            std::this_thread::sleep_for(std::chrono::microseconds((uint64_t)1e6) / (uint64_t)frequency_);
        }
        // std::cout << "dt: " << dt << " frequency: " << frequency_ << std::endl;
        */
	} //end for loop
	std::cout << "finished frequency " << frequency_ << std::endl;

}

std::thread ImagePublisher::run()
{
    stop_ = false;
    std::thread thread(&ImagePublisher::runThread, this);
    return thread;
}

void ImagePublisher::acqImgMsg()
{
  // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
  image_.subscriber_initalize_time(APP_TIME_CURRENT_US);
}

void ImagePublisher::preparImgMsg( const uint32_t frameNum )
{
  image_.frame_number(frameNum);
  image_.frequency(frequency_);
  image_.image(app::matToVecUchar(frame_));
  image_.width(frame_.cols);
  image_.height(frame_.rows);
}
bool ImagePublisher::publish(bool waitForListener, uint32_t frequency)
{
   // std::cout << "in publish frequency " << frequency << std::endl;
    if (listener_.firstConnected_ || !waitForListener || listener_.matched_ > 0)
    {
        image_.publisher_send_time(APP_TIME_CURRENT_US);
        writer_->write(&image_);
        return true;
    }
    return false;
}
