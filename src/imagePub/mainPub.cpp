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

/**
 * @file HelloWorld_main.cpp
 *
 */

#include "ImagePublisher.h"
#include "libUtil/util.h"

#include "libUtil/util.h"
#include "libUtil/AppLog.h"
#include "libUtil/readCfg.h"
#include "libCfg/Cfg.h"

using namespace std;
using namespace app;

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		cout << "pass a config file" << endl;
		return 0;
	}

	CfgPtr cfg = readCfg(argv[1]);

	printf("used cfg=<%s>\n", argv[1]);

	const string logFilename("logPub.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	uint32_t count = 10;
	uint32_t sleep_ms = 100;
	bool use_environment_qos = false;

	ImagePublisher mypub(cfg->getCam());
	if (mypub.init(use_environment_qos))
	{
		mypub.run(count, sleep_ms);
	}

	endLogThread();
	return 0;
}


//#include "opencv2/opencv.hpp"
//#include <time.h>
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char** argv)
//{
//
//    // Start default camera
//    VideoCapture video(0);
//
//    // With webcam get(CV_CAP_PROP_FPS) does not work.
//    // Let's see for ourselves.
//
//    // double fps = video.get(CV_CAP_PROP_FPS);
//    // If you do not care about backward compatibility
//    // You can use the following instead for OpenCV 3
//    double fps = video.get(CAP_PROP_FPS);
//    cout << "Frames per second using video.get(CAP_PROP_FPS) : " << fps << endl;
//
//    // Number of frames to capture
//    int num_frames = 120;
//
//    // Start and end times
//    time_t start, end;
//
//    // Variable for storing video frames
//    Mat frame;
//
//    cout << "Capturing " << num_frames << " frames" << endl;
//
//    // Start time
//    time(&start);
//
//    // Grab a few frames
//    for (int i = 0; i < num_frames; i++)
//    {
//        video >> frame;
//    }
//
//    // End Time
//    time(&end);
//
//    // Time elapsed
//    double seconds = difftime(end, start);
//    cout << "Time taken : " << seconds << " seconds" << endl;
//
//    // Calculate frames per second
//    fps = num_frames / seconds;
//    cout << "Estimated frames per second : " << fps << endl;
//
//    // Release video
//    video.release();
//    return 0;
//}