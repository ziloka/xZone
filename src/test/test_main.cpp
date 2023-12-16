#include "libUtil/AppLog.h"
#include "libUtil/Util.h"
#include "libCfg/Cfg.h"

#include <fastrtps/Domain.h>

#include "libHumiditySub/HumiditySubscriber.h"
#include "libImageSub/ImageSubscriber.h"
#include "libTemperatureSub/TemperatureSubscriber.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

int test_mat_part1(int argc, char* argv[]);

using namespace std;
using namespace eprosima::fastdds::dds;
using namespace app;

int main(int argc, char* argv[])
{
	bool use_environment_qos = false;
	const string logFilename("./logTestProcess.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	//thread humiditySubscriberThread(createHumiditySubscriber, use_environment_qos);

	thread imageSubscriberThread(createImageSubscriber, use_environment_qos);

	//thread temperatureSubscriberThread(createTemperatureSubscriber, use_environment_qos);
	
	//humiditySubscriberThread.join();
	imageSubscriberThread.join();
	//temperatureSubscriberThread.join();


	endLogThread();

	//Domain::stopAll();

	return 0;
}

