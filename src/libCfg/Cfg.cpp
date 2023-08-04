/*
*------------------------------------------------------------------------
*Cfg.cpp
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
#include "Cfg.h"

using namespace std;
using namespace app;

Cfg::Cfg()
	: m_log(new CfgLog())
{
}

void Cfg::readFromFile(const char *fname)
{
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::xml_parser::read_xml(fname, pt);
		this->fromPropertyTree(pt.get_child("cfg"));
		printf("xml read done!\n");
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
}

void Cfg::writeToFile(const char *fname)
{
	boost::property_tree::ptree pt = toPropertyTree();
	boost::property_tree::xml_parser::xml_writer_settings<std::string> settings(' ', 4);
	boost::property_tree::xml_parser::write_xml(fname, pt, std::locale(), settings);
}

std::string Cfg::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();

	std::ostringstream oss;
	boost::property_tree::xml_parser::xml_writer_settings<std::string> settings(' ', 4);
	boost::property_tree::xml_parser::write_xml(oss, pt, settings);
	return oss.str();
}

void Cfg::fromPropertyTree(const boost::property_tree::ptree &pt0)
{
	// set camera
	const boost::property_tree::ptree camPT = pt0.get_child("cam");
	CfgCamPtr cam( new CfgCam() );
	cam->fromPropertyTree(camPT);
	m_cam = cam;

	// set thermometer
	const boost::property_tree::ptree thermometerPT = pt0.get_child("thermometer");
	CfgThermometerPtr thermometer(new CfgThermometer());
	thermometer->fromPropertyTree(thermometerPT);
	m_thermometer = thermometer;

	// set hygrometer
	const boost::property_tree::ptree hygrometerPT = pt0.get_child("hygrometer");
	CfgHygrometerPtr hygrometer(new CfgHygrometer());
	hygrometer->fromPropertyTree(hygrometerPT);

	m_log->fromPropertyTree(pt0.get_child("log"));
}

boost::property_tree::ptree Cfg::toPropertyTree()
{
	boost::property_tree::ptree ptLog = m_log->toPropertyTree();
	boost::property_tree::ptree pt;
	boost::property_tree::ptree  ptCam = m_cam->toPropertyTree();
	pt.add_child( "cfg.cams.cam", ptCam );

	pt.add_child("cfg.log", ptLog);

	return pt;
}

void Cfg::updateRecFlag(bool isRecording) {
	boost::mutex::scoped_lock lock(m_mutex);
	m_cam->isRec_ = isRecording;
}

void Cfg::updateDispFlag(bool isDisp) {
	boost::mutex::scoped_lock lock(m_mutex);
	m_cam->isDisp_ = isDisp;
}

void Cfg::updateCamName(std::string name)
{
	boost::mutex::scoped_lock lock(m_mutex);
	m_cam->cameraName_ = name;
}
