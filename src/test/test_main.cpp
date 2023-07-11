#include "libUtil/util.h"
#include "libUtil/AppLog.h"
#include "libCfg/Cfg.h"

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

CfgPtr readCfg(string cfgFile)
{
	CfgPtr cfg(new Cfg());
	try {
		cfg->readFromFile(cfgFile.c_str());
	}
	catch (const std::overflow_error& e) {
		printf("overflow error: %s\n", e.what());
	}
	catch (const boost::property_tree::xml_parser::xml_parser_error& e) {
		printf("xml parse error: %s\n", e.what());
	}
	catch (const boost::property_tree::ptree_bad_path& e) {
		printf("ptree bad path: %s\n", e.what());
	}
	printf("cfg read successfully\n");

	return cfg;
}

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		cout << "pass a config file" << std::endl;
		return 0;
	}
	string cfgFile(argv[1]);
	printf("used cfg=<%s>\n", cfgFile.c_str());

	CfgPtr cfg = readCfg(cfgFile);



	//DomainParticipant* participant = DomainParticipantFactory::get_instance()->create_participant_with_profile(0, "participant_xml_profile");

	/*const string logFilename("./log.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	APP_LOG( "test1,i=%d", 10);
	APP_ASSERT(2 == 2, "xyz=%d,egg=%s", 3, "passed");
	APP_EXIT("xyz=%d,efg=%s", 2, "quit");
	endLogThread();*/


	return 0;
}
