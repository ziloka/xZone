/*
*------------------------------------------------------------------------
* CfgThermometer.cpp
*
* This code was developed by Shunguang Wu in his spare time. No government
* or any client funds were used.
*
*
* THE SOFTWARE IS PROVIDED AS-IS AND WITHOUT WARRANTY OF ANY KIND,
* EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
* WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
*
* IN NO EVENT SHALL THE AUTHOR OR DISTRIBUTOR BE LIABLE FOR
* ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
* OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
* WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
* LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
* OF THIS SOFTWARE.
*
* Permission to use, copy, modify, distribute, and sell this software and
* its documentation for any purpose is prohibited unless it is granted under
* the author's written notice.
*
* Copyright(c) 2020 by Shunguang Wu, All Right Reserved
*-------------------------------------------------------------------------
*/
#include "CfgThermometer.h"

using namespace std;
using namespace app;

CfgThermometer::CfgThermometer()
	: CfgBase()
	, thermometerId_(0)
	, thermometerName_("unkn")
	, frequency_(Frequency(10, 5, 100))
{

}

CfgThermometer::CfgThermometer(const CfgThermometer& x)
	: CfgBase(x)
	, thermometerId_(x.thermometerId_)
	, thermometerName_(x.thermometerName_)
	, frequency_(x.frequency_)
{
}

CfgThermometer& CfgThermometer::operator = (const CfgThermometer& x)
{
	//todo: m-thread unsafe
	if (this != &x) {
		CfgBase::operator=(x);
		thermometerId_ = x.thermometerId_;
		thermometerName_ = x.thermometerName_;
		frequency_ = x.frequency_;
	}
	return *this;
}

void CfgThermometer::fromPropertyTree(const boost::property_tree::ptree& pt)
{
	thermometerId_ = pt.get<int>("id");
	thermometerName_ = pt.get<std::string>("name");
	frequency_.start = pt.get<int>("frequencyStart");
	frequency_.step = pt.get<int>("frequencyStep");
	frequency_.end = pt.get<int>("frequencyEnd");
}

boost::property_tree::ptree CfgThermometer::toPropertyTree()
{
	boost::property_tree::ptree pt;

	pt.put("thermometerId", thermometerId_);
	pt.put("thermometerName", thermometerName_);
	pt.put("frequencyStart", frequency_.start);
	pt.put("frequencyStep", frequency_.step);
	pt.put("frequencyEnd", frequency_.end);
	return pt;
}

std::string CfgThermometer::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();
	return CfgBase::toString(pt);
}
