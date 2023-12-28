// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#ifndef IMAGESUBSCRIBER_H_
#define IMAGESUBSCRIBER_H_

#include "libMsg/ImagePubSubTypes.h"
#include "libCfg/Cfg.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>

#include <boost/filesystem.hpp>
#include "libUtil/Util.h"

class ImageSubscriber {
public:
  
    ImageSubscriber();

    virtual ~ImageSubscriber();

    //!Initialize the subscriber
    bool init(
            app::CfgPtr  cfg,
            bool use_env);

    //!RUN the subscriber
    void run();

    //!Run the subscriber until number samples have been received.
    void run(
            uint32_t number);

private:

    eprosima::fastdds::dds::DomainParticipant* participant_;

    eprosima::fastdds::dds::Subscriber* subscriber_;

    eprosima::fastdds::dds::Topic* topic_;

    eprosima::fastdds::dds::DataReader* reader_;

    eprosima::fastdds::dds::TypeSupport type_;

    class SubListener : public eprosima::fastdds::dds::DataReaderListener
    {
    public:

        SubListener()
            : matched_(0)
            , samples_(0)
            , file_(std::ofstream())
        {
            boost::filesystem::path dir("logs");

            if (!(boost::filesystem::exists(dir))) {
                std::cout << "logs folder doesn't Exist" << std::endl;

            if (boost::filesystem::create_directory(dir))
                    std::cout << "....Successfully Created logs folder !" << std::endl;
            }

            // https://stackoverflow.com/questions/38034033/c-localtime-this-function-or-variable-may-be-unsafe
            time_t t = std::time(nullptr);
            //tm tm = *std::localtime(&t);

            std::tm bt{};
            #if defined(__unix__)
                localtime_r(&t, &bt);
            #elif defined(_MSC_VER)
                localtime_s(&bt, &t);
            #else
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);
                bt = *std::localtime(&t);
            #endif

          //  auto dateTime = *std::put_time(&tm, "%d-%m-%Y %H-%M-%S")
            std::stringstream currentDateTime;
            currentDateTime << std::put_time(&bt, "%Y%m%d%H%M%S");
                //"%d-%m-%Y %H-%M-%S");
            std::string outPutFile = "logs/image_pubsub_data"+ currentDateTime.str() +".csv";
            file_.open(outPutFile, std::ofstream::out | std::ofstream::trunc);
            std::cout << "Opened " + outPutFile +"..appending to file" << std::endl;
            file_ << "frame number,image_height,image_width,publisher_sent,subscriber_received,frequency,latency,packets_receieved_count,transport" << std::endl;
        }

        ~SubListener() override
        {
        }

        void on_data_available(
            eprosima::fastdds::dds::DataReader* reader) override;

        void on_subscription_matched(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

        Image image_;

        int matched_;
      

        uint32_t samples_;

        std::stringstream output_data_stringstream_;
        std::ofstream file_;

        app::AppMeanStd<uint32_t> latencyStat_;
    } listener_;
};

void createImageSubscriber(app::CfgPtr cfg, bool use_environment_qos);

#endif /* IMAGESUBSCRIBER_H_ */
