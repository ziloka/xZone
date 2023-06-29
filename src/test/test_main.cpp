#include "libUtil/util.h"

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
	DomainParticipant* participant = DomainParticipantFactory::get_instance()->create_participant_with_profile(0, "participant_xml_profile");

	/*const string logFilename("./log.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	APP_LOG( "test1,i=%d", 10);
	APP_ASSERT(2 == 2, "xyz=%d,egg=%s", 3, "passed");
	APP_EXIT("xyz=%d,efg=%s", 2, "quit");
	endLogThread();*/
	return 0;
}

