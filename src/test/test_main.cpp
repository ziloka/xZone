#include "libutil/AppLog.h"
#include "libutil/util.h"
#include "libcfg/cfg.h"

#include "humiditySub/HumiditySubscriber.h"
#include "imageSub/ImageSubscriber.h"
#include "temperatureSub/TemperatureSubscriber.h"

#include <fastdds/dds/domain/domainparticipantfactory.hpp>
#include <fastdds/dds/domain/domainparticipant.hpp>
#include <fastdds/dds/topic/typesupport.hpp>
#include <fastdds/dds/publisher/publisher.hpp>
#include <fastdds/dds/publisher/datawriter.hpp>
#include <fastdds/dds/publisher/datawriterlistener.hpp>

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

	thread humiditySubscriberThread(createHumiditySubscriber, use_environment_qos);

	thread imageSubscriberThread(createImageSubscriber, use_environment_qos);

	thread temperatureSubscriberThread(createTemperatureSubscriber, use_environment_qos);
	
	humiditySubscriberThread.join();
	imageSubscriberThread.join();
	temperatureSubscriberThread.join();

	endLogThread();

	return 0;
}

