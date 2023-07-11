/*
*------------------------------------------------------------------------
* CfgHygrometer.cpp
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
#include "CfgHygrometer.h"

using namespace std;
using namespace app;

CfgHygrometer::CfgHygrometer()
	: CfgBase()
	, hygrometerId_(0)
	, hygrometerName_("unkn")
{

}

CfgHygrometer::CfgHygrometer(const CfgHygrometer& x)
	: CfgBase(x)
	, hygrometerId_(x.hygrometerId_)
	, hygrometerName_(x.hygrometerName_)
{
}

CfgHygrometer& CfgHygrometer::operator = (const CfgHygrometer& x)
{
	//todo: m-thread unsafe
	if (this != &x) {
		CfgBase::operator=(x);
		hygrometerId_ = x.hygrometerId_;
		hygrometerName_ = x.hygrometerName_;
	}
	return *this;
}

void CfgHygrometer::fromPropertyTree(const boost::property_tree::ptree& pt)
{
	hygrometerId_ = pt.get<int>("id");
	hygrometerName_ = pt.get<std::string>("name");
}

boost::property_tree::ptree CfgHygrometer::toPropertyTree()
{
	boost::property_tree::ptree pt;

	pt.put("id", hygrometerId_);
	pt.put("name", hygrometerName_);
	return pt;
}

std::string CfgHygrometer::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();
	return CfgBase::toString(pt);
}
