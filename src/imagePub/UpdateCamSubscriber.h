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

#ifndef UPDATECAMSUBSCRIBER_H_
#define UPDATECAMSUBSCRIBER_H_

#include "libMsg/UpdateCamPubSubTypes.h"
#include "libCfg/Cfg.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include "libUtil/Util.h"

#include <mutex>
#include <shared_mutex>

using namespace app;
using namespace eprosima::fastdds::dds;

// https://softwareengineering.stackexchange.com/questions/388977/how-to-reach-the-parent-object

class UpdateCamSubscriber;

class SubListener : public eprosima::fastdds::dds::DataReaderListener
{
public:

    SubListener(std::shared_ptr<std::shared_mutex> mutexPtr, UpdateCamSubscriber &updateCamSubscriber)
        : matched_(0)
        , samples_(0)
        , updateCamSubscriber_(updateCamSubscriber)
        , mutexPtr_(mutexPtr)
    {

    }

    ~SubListener() override
    {
    }

    void on_data_available(
        eprosima::fastdds::dds::DataReader* reader) override;

    void on_subscription_matched(
        eprosima::fastdds::dds::DataReader* reader,
        const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

    int matched_;

    uint32_t samples_;

    UpdateCam updateCam_;
private:
    UpdateCamSubscriber& updateCamSubscriber_;
    std::shared_ptr<std::shared_mutex> mutexPtr_;
};

class UpdateCamSubscriber
{
public:

    UpdateCamSubscriber(std::shared_ptr<std::shared_mutex> mutexPtr, CfgCamPtr cfgCamPtr);

    virtual ~UpdateCamSubscriber();

    //!Initialize the subscriber
    bool init(
        bool use_env);

    //!RUN the subscriber
    void run();

    //!Run the subscriber until number samples have been received.
    void run(
        uint32_t number);

    CfgCamPtr cfgCamPtr_;

private:

    eprosima::fastdds::dds::DomainParticipant* participant_;

    eprosima::fastdds::dds::Subscriber* subscriber_;

    eprosima::fastdds::dds::Topic* topic_;

    eprosima::fastdds::dds::DataReader* reader_;

    eprosima::fastdds::dds::TypeSupport type_;

    SubListener listener_;
};

void createUpdateCamSubscriber(std::shared_ptr<std::shared_mutex> mutex, std::shared_ptr<CfgCam> CfgCamPtr, bool use_environment_qos);

#endif /* UPDATECAMSUBSCRIBER_H_ */
