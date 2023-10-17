#pragma once
#ifndef __CFG_Hygrometer_H__
#define __CFG_Hygrometer_H__

#include "CfgBase.h"
namespace app {
	class  CFG_EXPORT CfgTransport : public CfgBase {
	public:
		CfgTransport();
		CfgTransport(const CfgTransport& x);
		CfgTransport& operator = (const CfgTransport& x);
		virtual ~CfgTransport() {};

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree& pt);
		virtual std::string toString();

	public:
		int			hygrometerId_;
		std::string hygrometerName_;
		Frequency   frequency_;


	};
	typedef std::shared_ptr<CfgTransport>		CfgTransportPtr;
}

#endif
