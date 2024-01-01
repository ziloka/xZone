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
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>
// #include <fastdds/rtps/attributes/ThreadSettings.hpp>

#include <fastrtps/utils/IPLocator.h>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <thread>
#include <list>

#include <iostream>
using namespace eprosima::fastdds::rtps;

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;

ImagePublisher::ImagePublisher(std::shared_ptr<std::shared_mutex> mutexPtr, CfgPtr cfgPtr, uint32_t fps)
    : participant_(nullptr)
    , publisher_(nullptr)
    , topic_(nullptr)
    , writer_(nullptr)
    , type_(new ImagePubSubType())
    , stop_(false)
{

    cfgPtr_ = cfgPtr;
    mutexPtr_ = mutexPtr;

    int height = cfgPtr->getCam().imgSz_.h;
    int width = cfgPtr->getCam().imgSz_.w;

    // there are 24 bits in a pixel using CV_8UC3 (3 bytes)
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
  //  std::cout << "in ImagePublisher::init" << std::endl;
    
    DomainParticipantQos participant_qos = PARTICIPANT_QOS_DEFAULT;
    participant_qos.name("ImagePublisher");


    PublishModeQosPolicy publish_mode;
     

    auto factory = DomainParticipantFactory::get_instance();

    if (factory == NULL) {
        // ... error
    }
    if (use_env)
    {
        factory->load_profiles();
        factory->get_default_participant_qos(participant_qos);
    }
    stop_ = false;
   
    // acts like server
    std::string wan_ip = "127.0.0.1";
    unsigned short port = 5100;

    switch (cfg->getTransport()) {
       
    case Transport::TCP: {
        //std::cout << "Using TCP as transport" << std::endl;
        std::shared_ptr<TCPv4TransportDescriptor> tcp_transport = std::make_shared<TCPv4TransportDescriptor>();
        tcp_transport = std::make_shared<TCPv4TransportDescriptor>();
        tcp_transport->add_listener_port(5100);
        tcp_transport->set_WAN_address("127.0.0.1");
        // Link the Transport Layer to the Participant.
        participant_qos.transport().user_transports.push_back(tcp_transport);

        tcp_transport->enable_tcp_nodelay = true;
        break;
    }
    case Transport::UDP: {
        //std::cout << "Using UDP as transport" << std::endl;
        std::shared_ptr<UDPv4TransportDescriptor> udp_transport = std::make_shared<UDPv4TransportDescriptor>();
        udp_transport->non_blocking_send = true;

        // Link the Transport Layer to the Participant.
        participant_qos.transport().user_transports.push_back(udp_transport);
        // Set use_builtin_transports to false
        participant_qos.transport().use_builtin_transports = false;
        
        break;
    }
    case Transport::SharedMemory: {
        //std::cout << "Using Shared memory as transport" << std::endl;

        // Create a descriptor for the new transport.
        std::shared_ptr<SharedMemTransportDescriptor> shm_transport = std::make_shared<SharedMemTransportDescriptor>();

        // Link the Transport Layer to the Participant.
        participant_qos.transport().user_transports.push_back(shm_transport);
        break;
    }
    default: {
        //std::cout << "Using FastDDS Default transport (UDP)" << std::endl;
        std::shared_ptr<UDPv4TransportDescriptor> my_transport = std::make_shared<UDPv4TransportDescriptor>();

        my_transport->sendBufferSize = 9216;
        my_transport->receiveBufferSize = 9216;
        my_transport->non_blocking_send = true;
        // Link the Transport Layer to the Participant.
        participant_qos.transport().user_transports.push_back(my_transport);
    }
    }

    // Limit to 300kb per second.
    static const char* flow_controller_name = FASTDDS_FLOW_CONTROLLER_DEFAULT;
    //"example_flow_controller";
    auto flow_control_300k_per_sec = std::make_shared
        <eprosima::fastdds::rtps::FlowControllerDescriptor>();
    flow_control_300k_per_sec->name = flow_controller_name;
    flow_control_300k_per_sec->scheduler = 
        eprosima::fastdds::rtps::FlowControllerSchedulerPolicy::FIFO;
    //flow_control_300k_per_sec->max_bytes_per_period = 300 * 1000;
    //0 value means no limit. 
    flow_control_300k_per_sec->max_bytes_per_period = 0;
    flow_control_300k_per_sec->period_ms = 1000;
    // Register flow controller on participant
    
    participant_qos.flow_controllers().push_back(flow_control_300k_per_sec);
    // .... create participant and publisher
   
    //std::cout << "trying to create participant" << std::endl;
    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participant_qos);
    //std::cout << "created participant" << std::endl;
    
    if (participant_ == nullptr)
    {
        return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    //CREATE THE PUBLISHER

    PublisherQos pubqos = PUBLISHER_QOS_DEFAULT;
  

    //publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT);
    publisher_ = participant_->create_publisher(
        pubqos,
        nullptr);
    if (publisher_ == nullptr)
    {
        return false;
    }

    //CREATE THE TOPIC
    topic_ = participant_->create_topic("ImageTopic",
        "Image", TOPIC_QOS_DEFAULT);

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
  //  wqos.history().kind = KEEP_LAST_HISTORY_QOS;
 //   wqos.history().depth = 30;
 //   wqos.resource_limits().max_samples = 50;
 //   wqos.resource_limits().allocated_samples = 20;
    wqos.reliable_writer_qos().times.heartbeatPeriod.seconds = 2;
    wqos.reliable_writer_qos().times.heartbeatPeriod.nanosec = 200 * 1000 * 1000;
    wqos.reliability().kind = RELIABLE_RELIABILITY_QOS;

    // Link writer to the registered flow controller.
   // Note that ASYNCHRONOUS_PUBLISH_MODE must be used

    //the asynch does not work.
    wqos.publish_mode().kind = ASYNCHRONOUS_PUBLISH_MODE;
    wqos.publish_mode().flow_controller_name = flow_controller_name;

    writer_ = publisher_->create_datawriter(topic_, wqos, &listener_);

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
       // std::cout << "delete_datawriter." << std::endl;
    }
    if (publisher_ != nullptr)
    {
        participant_->delete_publisher(publisher_);

       // std::cout << "delete_publisher." << std::endl;
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);

    //std::cout << "delete_participant." << std::endl;

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

 void ImagePublisher::runThread(int i)
{
     // create a queue of integer data type
     std::list<Image> image_list;
    const int numSamples = cfgPtr_->getCam().numSamples_;
    uint64_t tBeg = APP_TIME_CURRENT_NS;
    uint64_t tEnd = APP_TIME_CURRENT_NS;

   /* std::cout << "sending " << numSamples << " samples at " << frequency_ << std::endl;
    for (uint32_t i = 0; i < numSamples; i++) {*/
   
        acqImgMsg();
        preparImgMsg(i);

       // image_list.push_back(image_);
  
        //tEnd = APP_TIME_CURRENT_NS;

        //uint64_t dealayNanosecond = 1e9 / frequency_;
        //std::cout << "**dealayNanosecond " << dealayNanosecond  << std::endl;
        // 
        //wait utill delay time, interval
    
        //while (tEnd - tBeg <= dealayNanosecond) {
        //    tEnd = APP_TIME_CURRENT_NS;
        //   //uncomment this line to test if a delay is needed
        //   // std::cout << "**in while loop " << std::endl;
        //}
       
  
        if (!publish(false, numSamples)) {
            std::cout << "unable to send sample #" << i << std::endl;
        }
        //tBeg = APP_TIME_CURRENT_NS;
       //}
}


/*
void ImagePublisher::runThread(int i)
{
    acqImgMsg();
    preparImgMsg(i);

    // todo: make this thread
    if (!publish(false, cfgCam_.numSamples_)) {
        std::cout << "unable to send sample #" << i << std::endl;
    }
}
//std::cout << " published. " << i << std::endl;

*/

std::thread ImagePublisher::run(int i)
{
    stop_ = false;
    std::thread thread(&ImagePublisher::runThread, this, i);
    return thread;
}

/*
void ImagePublisher::runThread(int i)
{
	acqImgMsg();
	preparImgMsg(i);

           // todo: make this thread
        if (!publish(false, cfgCam_.numSamples_)) {
            std::cout << "unable to send sample #" << i << std::endl;
        }
    }
    //std::cout << " published. " << i << std::endl;
}


std::thread ImagePublisher::run(int i)
{
    stop_ = false;
    std::thread thread(&ImagePublisher::runThread, this, i);
    return thread;
}
*/

void ImagePublisher::acqImgMsg()
{
  // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
  image_.subscriber_initalize_time(APP_TIME_CURRENT_NS);
}

void ImagePublisher::preparImgMsg( const uint32_t frameNum )
{
  image_.frame_number(frameNum);
  image_.frequency(frequency_);
  image_.image(app::matToVecUchar(frame_));
  image_.width(frame_.cols);
  image_.height(frame_.rows);
  image_.transport(cfgPtr_->getTransport());
}

bool ImagePublisher::publish(bool waitForListener, uint32_t frequency)
//bool ImagePublisher::publish(bool waitForListener, uint32_t frequency, Image oneImage)
{
   // std::cout << "in publish frequency " << frequency << std::endl;
    if (listener_.firstConnected_ || !waitForListener || listener_.matched_ > 0)
    {
      //  std::cout << "in publish frequency " << frequency << std::endl;
        image_.publisher_send_time(APP_TIME_CURRENT_NS);
        writer_->write(&image_);
        return true;
    }
    return false;
}
