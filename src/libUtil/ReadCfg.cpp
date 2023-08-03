#include "ReadCfg.h"
#include "libCfg/Cfg.h"

using namespace std;
using namespace app;

namespace app {
	CfgPtr readCfg(char* cfgFile) {
		CfgPtr cfg(new Cfg()); 
		string filename(cfgFile);
		try {
			cfg->readFromFile(filename.c_str());
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

}
