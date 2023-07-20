// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/*!
 * @file UpdateCam.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "UpdateCam.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define UpdateCam_max_cdr_typesize 584ULL;
#define UpdateCam_max_key_cdr_typesize 0ULL;

UpdateCam::UpdateCam()
{
    // string m_rtspUrl
    m_rtspUrl ="";
    // long m_valid
    m_valid = 0;
    // long m_imgW
    m_imgW = 0;
    // long m_imgH
    m_imgH = 0;
    // long m_fpsNum
    m_fpsNum = 0;
    // long m_fpsDen
    m_fpsDen = 0;
    // long m_frmQueSz
    m_frmQueSz = 0;
    // long m_detPyrLev
    m_detPyrLev = 0;
    // long m_detMethodId
    m_detMethodId = 0;
    // long m_detNetworkId
    m_detNetworkId = 0;
    // long m_detFrmsToSkip
    m_detFrmsToSkip = 0;
    // string m_mp4LocationAndPrefix
    m_mp4LocationAndPrefix ="";
    // long long m_t1
    m_t1 = 0;
    // long long m_t2
    m_t2 = 0;
    // long long m_t3
    m_t3 = 0;

}

UpdateCam::~UpdateCam()
{















}

UpdateCam::UpdateCam(
        const UpdateCam& x)
{
    m_rtspUrl = x.m_rtspUrl;
    m_valid = x.m_valid;
    m_imgW = x.m_imgW;
    m_imgH = x.m_imgH;
    m_fpsNum = x.m_fpsNum;
    m_fpsDen = x.m_fpsDen;
    m_frmQueSz = x.m_frmQueSz;
    m_detPyrLev = x.m_detPyrLev;
    m_detMethodId = x.m_detMethodId;
    m_detNetworkId = x.m_detNetworkId;
    m_detFrmsToSkip = x.m_detFrmsToSkip;
    m_mp4LocationAndPrefix = x.m_mp4LocationAndPrefix;
    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;
}

UpdateCam::UpdateCam(
        UpdateCam&& x) noexcept 
{
    m_rtspUrl = std::move(x.m_rtspUrl);
    m_valid = x.m_valid;
    m_imgW = x.m_imgW;
    m_imgH = x.m_imgH;
    m_fpsNum = x.m_fpsNum;
    m_fpsDen = x.m_fpsDen;
    m_frmQueSz = x.m_frmQueSz;
    m_detPyrLev = x.m_detPyrLev;
    m_detMethodId = x.m_detMethodId;
    m_detNetworkId = x.m_detNetworkId;
    m_detFrmsToSkip = x.m_detFrmsToSkip;
    m_mp4LocationAndPrefix = std::move(x.m_mp4LocationAndPrefix);
    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;
}

UpdateCam& UpdateCam::operator =(
        const UpdateCam& x)
{

    m_rtspUrl = x.m_rtspUrl;
    m_valid = x.m_valid;
    m_imgW = x.m_imgW;
    m_imgH = x.m_imgH;
    m_fpsNum = x.m_fpsNum;
    m_fpsDen = x.m_fpsDen;
    m_frmQueSz = x.m_frmQueSz;
    m_detPyrLev = x.m_detPyrLev;
    m_detMethodId = x.m_detMethodId;
    m_detNetworkId = x.m_detNetworkId;
    m_detFrmsToSkip = x.m_detFrmsToSkip;
    m_mp4LocationAndPrefix = x.m_mp4LocationAndPrefix;
    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;

    return *this;
}

UpdateCam& UpdateCam::operator =(
        UpdateCam&& x) noexcept
{

    m_rtspUrl = std::move(x.m_rtspUrl);
    m_valid = x.m_valid;
    m_imgW = x.m_imgW;
    m_imgH = x.m_imgH;
    m_fpsNum = x.m_fpsNum;
    m_fpsDen = x.m_fpsDen;
    m_frmQueSz = x.m_frmQueSz;
    m_detPyrLev = x.m_detPyrLev;
    m_detMethodId = x.m_detMethodId;
    m_detNetworkId = x.m_detNetworkId;
    m_detFrmsToSkip = x.m_detFrmsToSkip;
    m_mp4LocationAndPrefix = std::move(x.m_mp4LocationAndPrefix);
    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;

    return *this;
}

bool UpdateCam::operator ==(
        const UpdateCam& x) const
{

    return (m_rtspUrl == x.m_rtspUrl && m_valid == x.m_valid && m_imgW == x.m_imgW && m_imgH == x.m_imgH && m_fpsNum == x.m_fpsNum && m_fpsDen == x.m_fpsDen && m_frmQueSz == x.m_frmQueSz && m_detPyrLev == x.m_detPyrLev && m_detMethodId == x.m_detMethodId && m_detNetworkId == x.m_detNetworkId && m_detFrmsToSkip == x.m_detFrmsToSkip && m_mp4LocationAndPrefix == x.m_mp4LocationAndPrefix && m_t1 == x.m_t1 && m_t2 == x.m_t2 && m_t3 == x.m_t3);
}

bool UpdateCam::operator !=(
        const UpdateCam& x) const
{
    return !(*this == x);
}

size_t UpdateCam::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return UpdateCam_max_cdr_typesize;
}

size_t UpdateCam::getCdrSerializedSize(
        const UpdateCam& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.rtspUrl().size() + 1;

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.mp4LocationAndPrefix().size() + 1;

    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);



    return current_alignment - initial_alignment;
}

void UpdateCam::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_rtspUrl.c_str();
    scdr << m_valid;
    scdr << m_imgW;
    scdr << m_imgH;
    scdr << m_fpsNum;
    scdr << m_fpsDen;
    scdr << m_frmQueSz;
    scdr << m_detPyrLev;
    scdr << m_detMethodId;
    scdr << m_detNetworkId;
    scdr << m_detFrmsToSkip;
    scdr << m_mp4LocationAndPrefix.c_str();
    scdr << m_t1;
    scdr << m_t2;
    scdr << m_t3;

}

void UpdateCam::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_rtspUrl;
    dcdr >> m_valid;
    dcdr >> m_imgW;
    dcdr >> m_imgH;
    dcdr >> m_fpsNum;
    dcdr >> m_fpsDen;
    dcdr >> m_frmQueSz;
    dcdr >> m_detPyrLev;
    dcdr >> m_detMethodId;
    dcdr >> m_detNetworkId;
    dcdr >> m_detFrmsToSkip;
    dcdr >> m_mp4LocationAndPrefix;
    dcdr >> m_t1;
    dcdr >> m_t2;
    dcdr >> m_t3;
}

/*!
 * @brief This function copies the value in member rtspUrl
 * @param _rtspUrl New value to be copied in member rtspUrl
 */
void UpdateCam::rtspUrl(
        const std::string& _rtspUrl)
{
    m_rtspUrl = _rtspUrl;
}

/*!
 * @brief This function moves the value in member rtspUrl
 * @param _rtspUrl New value to be moved in member rtspUrl
 */
void UpdateCam::rtspUrl(
        std::string&& _rtspUrl)
{
    m_rtspUrl = std::move(_rtspUrl);
}

/*!
 * @brief This function returns a constant reference to member rtspUrl
 * @return Constant reference to member rtspUrl
 */
const std::string& UpdateCam::rtspUrl() const
{
    return m_rtspUrl;
}

/*!
 * @brief This function returns a reference to member rtspUrl
 * @return Reference to member rtspUrl
 */
std::string& UpdateCam::rtspUrl()
{
    return m_rtspUrl;
}
/*!
 * @brief This function sets a value in member valid
 * @param _valid New value for member valid
 */
void UpdateCam::valid(
        int32_t _valid)
{
    m_valid = _valid;
}

/*!
 * @brief This function returns the value of member valid
 * @return Value of member valid
 */
int32_t UpdateCam::valid() const
{
    return m_valid;
}

/*!
 * @brief This function returns a reference to member valid
 * @return Reference to member valid
 */
int32_t& UpdateCam::valid()
{
    return m_valid;
}

/*!
 * @brief This function sets a value in member imgW
 * @param _imgW New value for member imgW
 */
void UpdateCam::imgW(
        int32_t _imgW)
{
    m_imgW = _imgW;
}

/*!
 * @brief This function returns the value of member imgW
 * @return Value of member imgW
 */
int32_t UpdateCam::imgW() const
{
    return m_imgW;
}

/*!
 * @brief This function returns a reference to member imgW
 * @return Reference to member imgW
 */
int32_t& UpdateCam::imgW()
{
    return m_imgW;
}

/*!
 * @brief This function sets a value in member imgH
 * @param _imgH New value for member imgH
 */
void UpdateCam::imgH(
        int32_t _imgH)
{
    m_imgH = _imgH;
}

/*!
 * @brief This function returns the value of member imgH
 * @return Value of member imgH
 */
int32_t UpdateCam::imgH() const
{
    return m_imgH;
}

/*!
 * @brief This function returns a reference to member imgH
 * @return Reference to member imgH
 */
int32_t& UpdateCam::imgH()
{
    return m_imgH;
}

/*!
 * @brief This function sets a value in member fpsNum
 * @param _fpsNum New value for member fpsNum
 */
void UpdateCam::fpsNum(
        int32_t _fpsNum)
{
    m_fpsNum = _fpsNum;
}

/*!
 * @brief This function returns the value of member fpsNum
 * @return Value of member fpsNum
 */
int32_t UpdateCam::fpsNum() const
{
    return m_fpsNum;
}

/*!
 * @brief This function returns a reference to member fpsNum
 * @return Reference to member fpsNum
 */
int32_t& UpdateCam::fpsNum()
{
    return m_fpsNum;
}

/*!
 * @brief This function sets a value in member fpsDen
 * @param _fpsDen New value for member fpsDen
 */
void UpdateCam::fpsDen(
        int32_t _fpsDen)
{
    m_fpsDen = _fpsDen;
}

/*!
 * @brief This function returns the value of member fpsDen
 * @return Value of member fpsDen
 */
int32_t UpdateCam::fpsDen() const
{
    return m_fpsDen;
}

/*!
 * @brief This function returns a reference to member fpsDen
 * @return Reference to member fpsDen
 */
int32_t& UpdateCam::fpsDen()
{
    return m_fpsDen;
}

/*!
 * @brief This function sets a value in member frmQueSz
 * @param _frmQueSz New value for member frmQueSz
 */
void UpdateCam::frmQueSz(
        int32_t _frmQueSz)
{
    m_frmQueSz = _frmQueSz;
}

/*!
 * @brief This function returns the value of member frmQueSz
 * @return Value of member frmQueSz
 */
int32_t UpdateCam::frmQueSz() const
{
    return m_frmQueSz;
}

/*!
 * @brief This function returns a reference to member frmQueSz
 * @return Reference to member frmQueSz
 */
int32_t& UpdateCam::frmQueSz()
{
    return m_frmQueSz;
}

/*!
 * @brief This function sets a value in member detPyrLev
 * @param _detPyrLev New value for member detPyrLev
 */
void UpdateCam::detPyrLev(
        int32_t _detPyrLev)
{
    m_detPyrLev = _detPyrLev;
}

/*!
 * @brief This function returns the value of member detPyrLev
 * @return Value of member detPyrLev
 */
int32_t UpdateCam::detPyrLev() const
{
    return m_detPyrLev;
}

/*!
 * @brief This function returns a reference to member detPyrLev
 * @return Reference to member detPyrLev
 */
int32_t& UpdateCam::detPyrLev()
{
    return m_detPyrLev;
}

/*!
 * @brief This function sets a value in member detMethodId
 * @param _detMethodId New value for member detMethodId
 */
void UpdateCam::detMethodId(
        int32_t _detMethodId)
{
    m_detMethodId = _detMethodId;
}

/*!
 * @brief This function returns the value of member detMethodId
 * @return Value of member detMethodId
 */
int32_t UpdateCam::detMethodId() const
{
    return m_detMethodId;
}

/*!
 * @brief This function returns a reference to member detMethodId
 * @return Reference to member detMethodId
 */
int32_t& UpdateCam::detMethodId()
{
    return m_detMethodId;
}

/*!
 * @brief This function sets a value in member detNetworkId
 * @param _detNetworkId New value for member detNetworkId
 */
void UpdateCam::detNetworkId(
        int32_t _detNetworkId)
{
    m_detNetworkId = _detNetworkId;
}

/*!
 * @brief This function returns the value of member detNetworkId
 * @return Value of member detNetworkId
 */
int32_t UpdateCam::detNetworkId() const
{
    return m_detNetworkId;
}

/*!
 * @brief This function returns a reference to member detNetworkId
 * @return Reference to member detNetworkId
 */
int32_t& UpdateCam::detNetworkId()
{
    return m_detNetworkId;
}

/*!
 * @brief This function sets a value in member detFrmsToSkip
 * @param _detFrmsToSkip New value for member detFrmsToSkip
 */
void UpdateCam::detFrmsToSkip(
        int32_t _detFrmsToSkip)
{
    m_detFrmsToSkip = _detFrmsToSkip;
}

/*!
 * @brief This function returns the value of member detFrmsToSkip
 * @return Value of member detFrmsToSkip
 */
int32_t UpdateCam::detFrmsToSkip() const
{
    return m_detFrmsToSkip;
}

/*!
 * @brief This function returns a reference to member detFrmsToSkip
 * @return Reference to member detFrmsToSkip
 */
int32_t& UpdateCam::detFrmsToSkip()
{
    return m_detFrmsToSkip;
}

/*!
 * @brief This function copies the value in member mp4LocationAndPrefix
 * @param _mp4LocationAndPrefix New value to be copied in member mp4LocationAndPrefix
 */
void UpdateCam::mp4LocationAndPrefix(
        const std::string& _mp4LocationAndPrefix)
{
    m_mp4LocationAndPrefix = _mp4LocationAndPrefix;
}

/*!
 * @brief This function moves the value in member mp4LocationAndPrefix
 * @param _mp4LocationAndPrefix New value to be moved in member mp4LocationAndPrefix
 */
void UpdateCam::mp4LocationAndPrefix(
        std::string&& _mp4LocationAndPrefix)
{
    m_mp4LocationAndPrefix = std::move(_mp4LocationAndPrefix);
}

/*!
 * @brief This function returns a constant reference to member mp4LocationAndPrefix
 * @return Constant reference to member mp4LocationAndPrefix
 */
const std::string& UpdateCam::mp4LocationAndPrefix() const
{
    return m_mp4LocationAndPrefix;
}

/*!
 * @brief This function returns a reference to member mp4LocationAndPrefix
 * @return Reference to member mp4LocationAndPrefix
 */
std::string& UpdateCam::mp4LocationAndPrefix()
{
    return m_mp4LocationAndPrefix;
}
/*!
 * @brief This function sets a value in member t1
 * @param _t1 New value for member t1
 */
void UpdateCam::t1(
        int64_t _t1)
{
    m_t1 = _t1;
}

/*!
 * @brief This function returns the value of member t1
 * @return Value of member t1
 */
int64_t UpdateCam::t1() const
{
    return m_t1;
}

/*!
 * @brief This function returns a reference to member t1
 * @return Reference to member t1
 */
int64_t& UpdateCam::t1()
{
    return m_t1;
}

/*!
 * @brief This function sets a value in member t2
 * @param _t2 New value for member t2
 */
void UpdateCam::t2(
        int64_t _t2)
{
    m_t2 = _t2;
}

/*!
 * @brief This function returns the value of member t2
 * @return Value of member t2
 */
int64_t UpdateCam::t2() const
{
    return m_t2;
}

/*!
 * @brief This function returns a reference to member t2
 * @return Reference to member t2
 */
int64_t& UpdateCam::t2()
{
    return m_t2;
}

/*!
 * @brief This function sets a value in member t3
 * @param _t3 New value for member t3
 */
void UpdateCam::t3(
        int64_t _t3)
{
    m_t3 = _t3;
}

/*!
 * @brief This function returns the value of member t3
 * @return Value of member t3
 */
int64_t UpdateCam::t3() const
{
    return m_t3;
}

/*!
 * @brief This function returns a reference to member t3
 * @return Reference to member t3
 */
int64_t& UpdateCam::t3()
{
    return m_t3;
}



size_t UpdateCam::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return UpdateCam_max_key_cdr_typesize;
}

bool UpdateCam::isKeyDefined()
{
    return false;
}

void UpdateCam::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}

