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

#ifndef UPDATEHYGROMETERSUBSCRIBER_H_
#define UPDATEHYGROMETERSUBSCRIBER_H_

#include "libMsg/UpdateHygrometerPubSubTypes.h"
#include "libCfg/Cfg.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include "libUtil/util.h"

#include <mutex>
#include <shared_mutex>

using namespace app;
using namespace eprosima::fastdds::dds;

// https://softwareengineering.stackexchange.com/questions/388977/how-to-reach-the-parent-object

class UpdateHygrometerSubscriber;

class SubListener : public eprosima::fastdds::dds::DataReaderListener
{
public:

    SubListener(std::shared_ptr<std::shared_mutex> mutexPtr, UpdateHygrometerSubscriber& updateHygrometerSubscriber)
        : matched_(0)
        , samples_(0)
        , updateHygrometerSubscriber_(updateHygrometerSubscriber)
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

    UpdateHygrometer updateCam_;
private:
    UpdateHygrometerSubscriber& updateHygrometerSubscriber_;
    std::shared_ptr<std::shared_mutex> mutexPtr_;
};

class UpdateHygrometerSubscriber
{
public:

    UpdateHygrometerSubscriber(std::shared_ptr<std::shared_mutex> mutexPtr, CfgHygrometerPtr cfgHygrometerPtr);

    virtual ~UpdateHygrometerSubscriber();

    //!Initialize the subscriber
    bool init(
        bool use_env);

    //!RUN the subscriber
    void run();

    //!Run the subscriber until number samples have been received.
    void run(
        uint32_t number);

    CfgHygrometerPtr cfgHygrometerPtr_;

private:

    eprosima::fastdds::dds::DomainParticipant* participant_;

    eprosima::fastdds::dds::Subscriber* subscriber_;

    eprosima::fastdds::dds::Topic* topic_;

    eprosima::fastdds::dds::DataReader* reader_;

    eprosima::fastdds::dds::TypeSupport type_;

    SubListener listener_;
};

void createUpdateHygrometerSubscriber(std::shared_ptr<std::shared_mutex> mutex, std::shared_ptr<CfgHygrometer> CfgCamPtr, bool use_environment_qos);

#endif /* UPDATEHYGROMETERSUBSCRIBER_H_ */
