#include <fastdds/dds/publisher/DataWriterListener.hpp>

using namespace eprosima::fastdds::dds;

#pragma once
class CustomDataWriterListener : public DataWriterListener
{

public:

    CustomDataWriterListener()
        : DataWriterListener()
    {
    }

    virtual ~CustomDataWriterListener()
    {
    }

    

};