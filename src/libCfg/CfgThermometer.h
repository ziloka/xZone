
#ifndef __CFG_THERMOETER_H__
#define __CFG_THERMOETER_H__

#include "CfgBase.h"
namespace app {
	class  CFG_EXPORT CfgThermometer : public CfgBase {
	public:
		CfgThermometer();
		CfgThermometer(const CfgThermometer& x);
		CfgThermometer& operator = (const CfgThermometer& x);
		virtual ~CfgThermometer() {};

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree& pt);
		virtual std::string toString();

		//uint32_t	getIp() const;
	public:
		int			thermometerId_;
		std::string thermometerName_;
		Frequency frequency_;


	};
	typedef std::shared_ptr<CfgThermometer>		CfgThermometerPtr;
}

#endif
