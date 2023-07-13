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

#include <memory>

#include "UpdateCamSubscriber.h"
#include "ImagePublisher.h"
#include "libUtil/util.h"

#include "libUtil/util.h"
#include "libUtil/AppLog.h"
#include "libUtil/readCfg.h"
#include "libCfg/Cfg.h"


#include <mutex>
#include <shared_mutex>

using namespace app;

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		std::cout << "pass a config file" << std::endl;
		return 0;
	}

	// visual studio debugging purposes
	std::cout << std::filesystem::current_path() << std::endl;

	CfgPtr cfg = readCfg(argv[1]);

	std::printf("used cfg=<%s>\n", argv[1]);

	const std::string logFilename("logPub.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	uint32_t count = 10;
	uint32_t sleep_ms = 100;
	bool use_environment_qos = false;

	std::shared_ptr<std::shared_mutex> mutex;
	std::shared_ptr<CfgCam> CfgCamPtr = std::make_shared<CfgCam>(cfg->getCam());
	ImagePublisher mypub(mutex, CfgCamPtr);
	if (mypub.init(use_environment_qos))
	{
		std::thread subscriber(createUpdateCamSubscriber, mutex, CfgCamPtr, use_environment_qos);
		std::thread publisher = mypub.run(count, sleep_ms);
		publisher.join();
		subscriber.join();
	}

	endLogThread();
	return 0;
}