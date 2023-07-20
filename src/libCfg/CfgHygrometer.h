#ifndef __CFG_Hygrometer_H__
#define __CFG_Hygrometer_H__

#include "CfgBase.h"
namespace app {
	class  CFG_EXPORT CfgHygrometer : public CfgBase {
	public:
		CfgHygrometer();
		CfgHygrometer(const CfgHygrometer& x);
		CfgHygrometer& operator = (const CfgHygrometer& x);
		virtual ~CfgHygrometer() {};

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree& pt);
		virtual std::string toString();

		//uint32_t	getIp() const;
	public:
		int			hygrometerId_;
		std::string hygrometerName_;


	};
	typedef std::shared_ptr<CfgHygrometer>		CfgHygrometerPtr;
}

#endif
