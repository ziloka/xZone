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
#include "libMsg/ImageTypeObject.h"
#include "libUtil/Util.h"

#include "libUtil/AppLog.h"
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

	CfgPtr cfg(new Cfg());
	cfg->readFromFile(argv[1]);

	std::printf("used cfg=<%s>\n", argv[1]);

	const std::string logFilename("logPub.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	bool use_environment_qos = true;

	std::shared_ptr<std::shared_mutex> mutex;

	// std::thread subscriber(createUpdateCamSubscriber, mutex, cfg, use_environment_qos);
	// subscriber.join();

	
	registerImageTypes();
	// pass hz frequency param
	// std::vector<std::thread> threads;
	const int numSamples = cfg->getCam().numSamples_;
	for (double hz = cfg->getCam().frequency_.start; hz <= cfg->getCam().frequency_.end; hz += cfg->getCam().frequency_.step) {
		std::cout << "On frequency #" << hz << std::endl << std::endl;
		std::cout << "sending " << numSamples << " samples at " << hz << std::endl;

		long tBeg = APP_TIME_CURRENT_NS;
		long tEnd = APP_TIME_CURRENT_NS;

			//wait utill delay time, interval
			/*
			do {
				tEnd = APP_TIME_CURRENT_NS;
				// std::cout << " do loop " << i << std::endl;
			} while (tEnd - tBeg <= dealayNanosecond);
			*/

		ImagePublisher mypub(mutex, cfg, hz);
		
		if (mypub.init(cfg, use_environment_qos)) {
		//	for (uint32_t i = 0; i <= numSamples; i++) {

		//		tBeg = APP_TIME_CURRENT_NS;
		//		long dealayNanosecond = 1e9 / hz;

				std::thread publisher = mypub.run();
				publisher.join();
		//	}
		//	tEnd = APP_TIME_CURRENT_NS;
		}

		//end for loop
		std::cout << "in MainPub finished frequency " << hz << std::endl;
	}

	app::endLogThread();
	return 0;
}

/*
{
		auto [start, step, end] = cfgCamPtr_->frequency_;
		for (uint32_t iFreq = start; nSamples < end; nSamples += step) {
		}
}

*/