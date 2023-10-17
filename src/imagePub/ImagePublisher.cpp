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

ImagePublisher::ImagePublisher(std::shared_ptr<std::shared_mutex> mutexPtr, CfgPtr cfgPtr)
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

    DomainParticipantQos pqos = PARTICIPANT_QOS_DEFAULT;
    pqos.name("ImagePublisher");
    auto factory = DomainParticipantFactory::get_instance();

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
        tcp_transport->add_listener_port(5100);
        tcp_transport->set_WAN_address("127.0.0.1");

        // Link the Transport Layer to the Participant.
        pqos.transport().user_transports.push_back(tcp_transport);
        break;
    }
    case 2: {
        std::cout << "Using UDP as transport" << std::endl;
        std::shared_ptr<eprosima::fastdds::rtps::UDPv4TransportDescriptor> udp_transport = std::make_shared<eprosima::fastdds::rtps::UDPv4TransportDescriptor>();
        udp_transport->sendBufferSize = 9216;
        udp_transport->receiveBufferSize = 9216;
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

    participant_ = factory->create_participant(0, pqos);

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
    }
    if (publisher_ != nullptr)
    {
        participant_->delete_publisher(publisher_);
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
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
    const int nFreqHz = cfgCam_.nFreqHz_;
    const int nanoseconds_per_msg = 1000000000 / nFreqHz;

	// there are 1,000,000,000 nanoseconds in a second

	std::cout << "sending " << numSamples << " samples" << std::endl;
	for (uint32_t i = 0; i < numSamples; i++) {
        uint64_t tBeg = APP_TIME_CURRENT_US;
		acqImgMsg();
		preparImgMsg(i);
		if (!publish(false, numSamples)) {
			std::cout << "unable to send sample #" << i << std::endl;
		}

        uint64_t tEnd = APP_TIME_CURRENT_US;
        uint64_t dt = tEnd - tBeg;
        if ( dt < nanoseconds_per_msg) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(nanoseconds_per_msg - dt));
        }
	}
	std::cout << "sent " << numSamples << " samples" << std::endl;

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
  image_.t1(APP_TIME_CURRENT_US);
}

void ImagePublisher::preparImgMsg( const uint32_t frameNum )
{
  image_.frame_number(frameNum);
  image_.image(app::matToVecUchar(frame_));
  image_.width(frame_.cols);
  image_.height(frame_.rows);
}
bool ImagePublisher::publish(bool waitForListener, uint32_t frequency)
{
    if (listener_.firstConnected_ || !waitForListener || listener_.matched_ > 0)
    {
        image_.t2(APP_TIME_CURRENT_US);
        writer_->write(&image_);
        return true;
    }
    return false;
}
