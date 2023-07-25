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

#include "ImageSubscriber.h"
#include "UpdateCamPublisher.h"
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

using namespace eprosima::fastdds::dds;
using namespace app;

ImageSubscriber::ImageSubscriber()
    : participant_(nullptr)
    , subscriber_(nullptr)
    , topic_(nullptr)
    , reader_(nullptr)
    , type_(new ImagePubSubType())
{
}

bool ImageSubscriber::init(
        bool use_env)
{
    DomainParticipantQos pqos = PARTICIPANT_QOS_DEFAULT;
    pqos.name("ImageSubscriber");
    auto factory = DomainParticipantFactory::get_instance();

    if (use_env)
    {
        factory->load_profiles();
        factory->get_default_participant_qos(pqos);
    }

    participant_ = factory->create_participant(0, pqos);

    if (participant_ == nullptr)
    {
        return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    //CREATE THE SUBSCRIBER
    SubscriberQos sqos = SUBSCRIBER_QOS_DEFAULT;

    if (use_env)
    {
        participant_->get_default_subscriber_qos(sqos);
    }

    subscriber_ = participant_->create_subscriber(sqos, nullptr);

    if (subscriber_ == nullptr)
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

    // CREATE THE READER
    DataReaderQos rqos = DATAREADER_QOS_DEFAULT;
    rqos.reliability().kind = RELIABLE_RELIABILITY_QOS;

    if (use_env)
    {
        subscriber_->get_default_datareader_qos(rqos);
    }

    reader_ = subscriber_->create_datareader(topic_, rqos, &listener_);

    if (reader_ == nullptr)
    {
        return false;
    }

    return true;
}

ImageSubscriber::~ImageSubscriber()
{
    if (reader_ != nullptr)
    {
        subscriber_->delete_datareader(reader_);
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    if (subscriber_ != nullptr)
    {
        participant_->delete_subscriber(subscriber_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

void ImageSubscriber::SubListener::on_subscription_matched(
        DataReader*,
        const SubscriptionMatchedStatus& info)
{
    if (info.current_count_change == 1)
    {
        matched_ = info.total_count;
        std::cout << "Subscriber matched." << std::endl;

        std::thread updateCamPublisher(createUpdateCamPublisher, false);
        updateCamPublisher.join();
    }
    else if (info.current_count_change == -1)
    {
        matched_ = info.total_count;
        std::cout << "Subscriber unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void ImageSubscriber::SubListener::on_data_available(  DataReader* reader)
{
    SampleInfo info;
    if (reader->take_next_sample(&image_, &info) == ReturnCode_t::RETCODE_OK)
    {
        if (info.instance_state == ALIVE_INSTANCE_STATE)
        {
            samples_++;
            // Print your structure data here.

            //while (1) {

            //    cv::Mat frame;
            //    frame = app::vecUcharToMat(image_.image(), image_.width(), image_.height());

            //    // Display the resulting frame
            //    cv::imshow("Frame", frame);

            //    // Press  ESC on keyboard to exit
            //    char c = (char) cv::waitKey(25);
            //    if (c == 27)
            //        break;
            //}

            //APP_LOG("frame number=%u received, time captured (t1)=%u, time sent msg out (t2)=%u, time received msg (t3)=%u", image_.frame_number(), image_.t1(), image_.t2(), APP_TIME_CURRENT_US);

            // write data to data.csv file 
            // frame number, frequency, latency
            file_ << image_.frame_number() << "," << image_.frequency() << "," << APP_TIME_CURRENT_US - image_.t2() << std::endl;
            
        }
    }
}

void ImageSubscriber::run()
{
  APP_LOG("subscriber running. Please press enter to stop the Subscriber");
  std::cin.ignore();
}

void ImageSubscriber::run(uint32_t number)
{
    std::cout << "Subscriber running until " << number << "samples have been received" << std::endl;
    while (number > listener_.samples_)
    {
      APP_LOG("HelloWorldSubscriber::run(): sleep 500 ms");
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void createImageSubscriber(bool use_environment_qos) {
    ImageSubscriber imageSubscriber;
    if (imageSubscriber.init(use_environment_qos)) imageSubscriber.run();
}