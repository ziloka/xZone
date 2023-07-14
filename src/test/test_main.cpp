#include "libutil/util.h"
#include "libutil/applog.h"
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

//CfgPtr readcfg(string cfgfile)
//{
//	CfgPtr cfg(new Cfg());
//	try {
//		cfg->readFromFile(cfgfile.c_str());
//	}
//	catch (const std::overflow_error& e) {
//		printf("overflow error: %s\n", e.what());
//	}
//	catch (const boost::property_tree::xml_parser::xml_parser_error& e) {
//		printf("xml parse error: %s\n", e.what());
//	}
//	catch (const boost::property_tree::ptree_bad_path& e) {
//		printf("ptree bad path: %s\n", e.what());
//	}
//	printf("cfg read successfully\n");
//
//	return cfg;
//}

int main(int argc, char* argv[])
{
	//if (argc <= 1) {
	//	cout << "pass a config file" << std::endl;
	//	return 0;
	//}
	//string cfgfile(argv[1]);
	//printf("used cfg=<%s>\n", cfgfile.c_str());

	//CfgPtr cfg = readCfg(cfgfile);

	bool use_environment_qos = false;
	const bool showInConsole = true;

	HumiditySubscriber humiditySubscriber;
	if (humiditySubscriber.init(use_environment_qos)) humiditySubscriber.run();

	ImageSubscriber imageSubscriber;
	if (imageSubscriber.init(use_environment_qos)) imageSubscriber.run();

	TemperatureSubscriber temperatureSubscriber;
	if (temperatureSubscriber.init(use_environment_qos)) temperatureSubscriber.run();
	

	return 0;
}