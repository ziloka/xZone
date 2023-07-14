//#include "libUtil/util.h"
//#include "libUtil/AppLog.h"
//#include "libCfg/Cfg.h"
//
//#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
//#include <fastdds/dds/domain/DomainParticipant.hpp>
//#include <fastdds/dds/topic/TypeSupport.hpp>
//#include <fastdds/dds/publisher/Publisher.hpp>
//#include <fastdds/dds/publisher/DataWriter.hpp>
//#include <fastdds/dds/publisher/DataWriterListener.hpp>
//
//int test_mat_part1(int argc, char* argv[]);
//
//using namespace std;
//using namespace eprosima::fastdds::dds;
//using namespace app;
//
//CfgPtr readCfg(string cfgFile)
//{
//	CfgPtr cfg(new Cfg());
//	try {
//		cfg->readFromFile(cfgFile.c_str());
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
//
//int main(int argc, char* argv[])
//{
//	if (argc <= 1) {
//		cout << "pass a config file" << std::endl;
//		return 0;
//	}
//	string cfgFile(argv[1]);
//	printf("used cfg=<%s>\n", cfgFile.c_str());
//
//	CfgPtr cfg = readCfg(cfgFile);
//
//
//
//	//DomainParticipant* participant = DomainParticipantFactory::get_instance()->create_participant_with_profile(0, "participant_xml_profile");
//
//	/*const string logFilename("./log.txt");
//	const bool showInConsole = true;
//	startLogThread(logFilename, showInConsole);
//
//	APP_LOG( "test1,i=%d", 10);
//	APP_ASSERT(2 == 2, "xyz=%d,egg=%s", 3, "passed");
//	APP_EXIT("xyz=%d,efg=%s", 2, "quit");
//	endLogThread();*/
//
//
//	return 0;
//}


//#include <opencv2/core.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <iostream>
//#include <stdio.h>
//using namespace cv;
//using namespace std;
//int main(int, char**) {
//	Mat frame;
//	//--- INITIALIZE VIDEOCAPTURE
//	VideoCapture cap;
//	// open the default camera using default API
//	// cap.open(0);
//	// OR advance usage: select any API backend
//	int deviceID = 0; // 0 = open default camera
//	int apiID = cv::CAP_ANY; // 0 = autodetect default API
//	// open selected camera using selected API
//	cap.open(deviceID + apiID);
//	// check if we succeeded
//	if (!cap.isOpened()) {
//		cerr << "ERROR! Unable to open camera\n";
//		return -1;
//	}
//	//--- GRAB AND WRITE LOOP
//	cout << "Start grabbing" << endl
//		<< "Press any key to terminate" << endl;
//	for (;;)
//	{
//		// wait for a new frame from camera and store it into 'frame'
//		cap.read(frame);
//		// check if we succeeded
//		if (frame.empty()) {
//			cerr << "ERROR! blank frame grabbed\n";
//			break;
//		}
//		// show live and wait for a key with timeout long enough to show images
//		imshow("Live", frame);
//		if (waitKey(5) >= 0)
//			break;
//	}
//	// the camera will be deinitialized automatically in VideoCapture destructor
//	return 0;
//}

//#include <opencv2/core/core.hpp> 
//#include <opencv2/highgui/highgui.hpp> 
//using namespace cv;
//int main()
//{
//    Mat img = imread("./girl.jpg");
//    namedWindow("opencv");
//    imshow("opencv", img);
//    waitKey(6000);
//
//    return 0;
//}


#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
    Mat image;
    String inputName;

    for (int i = 1; i < argc; i++)
    {
        inputName.assign(argv[i]);
    }

    if (inputName.empty() || (isdigit(inputName.c_str()[0]) && inputName.c_str()[1] == '\0'))
    {
        if (inputName.size())
        {
            image = imread(inputName, 1);
        }
        else
        {
            if (image.empty()) cout << "Couldn't read image" << endl;
        }
        imshow("Test", image);
    }
}