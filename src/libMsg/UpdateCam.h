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
 * @file UpdateCam.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_UPDATECAM_H_
#define _FAST_DDS_GENERATED_UPDATECAM_H_


#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(UPDATECAM_SOURCE)
#define UPDATECAM_DllAPI __declspec( dllexport )
#else
#define UPDATECAM_DllAPI __declspec( dllimport )
#endif // UPDATECAM_SOURCE
#else
#define UPDATECAM_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define UPDATECAM_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


/*!
 * @brief This class represents the structure UpdateCam defined by the user in the IDL file.
 * @ingroup UpdateCam
 */
class UpdateCam
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport UpdateCam();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~UpdateCam();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object UpdateCam that will be copied.
     */
    eProsima_user_DllExport UpdateCam(
            const UpdateCam& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object UpdateCam that will be copied.
     */
    eProsima_user_DllExport UpdateCam(
            UpdateCam&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object UpdateCam that will be copied.
     */
    eProsima_user_DllExport UpdateCam& operator =(
            const UpdateCam& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object UpdateCam that will be copied.
     */
    eProsima_user_DllExport UpdateCam& operator =(
            UpdateCam&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x UpdateCam object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const UpdateCam& x) const;

    /*!
     * @brief Comparison operator.
     * @param x UpdateCam object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const UpdateCam& x) const;

    /*!
     * @brief This function copies the value in member rtspUrl
     * @param _rtspUrl New value to be copied in member rtspUrl
     */
    eProsima_user_DllExport void rtspUrl(
            const std::string& _rtspUrl);

    /*!
     * @brief This function moves the value in member rtspUrl
     * @param _rtspUrl New value to be moved in member rtspUrl
     */
    eProsima_user_DllExport void rtspUrl(
            std::string&& _rtspUrl);

    /*!
     * @brief This function returns a constant reference to member rtspUrl
     * @return Constant reference to member rtspUrl
     */
    eProsima_user_DllExport const std::string& rtspUrl() const;

    /*!
     * @brief This function returns a reference to member rtspUrl
     * @return Reference to member rtspUrl
     */
    eProsima_user_DllExport std::string& rtspUrl();
    /*!
     * @brief This function sets a value in member valid
     * @param _valid New value for member valid
     */
    eProsima_user_DllExport void valid(
            int32_t _valid);

    /*!
     * @brief This function returns the value of member valid
     * @return Value of member valid
     */
    eProsima_user_DllExport int32_t valid() const;

    /*!
     * @brief This function returns a reference to member valid
     * @return Reference to member valid
     */
    eProsima_user_DllExport int32_t& valid();

    /*!
     * @brief This function sets a value in member imgW
     * @param _imgW New value for member imgW
     */
    eProsima_user_DllExport void imgW(
            int32_t _imgW);

    /*!
     * @brief This function returns the value of member imgW
     * @return Value of member imgW
     */
    eProsima_user_DllExport int32_t imgW() const;

    /*!
     * @brief This function returns a reference to member imgW
     * @return Reference to member imgW
     */
    eProsima_user_DllExport int32_t& imgW();

    /*!
     * @brief This function sets a value in member imgH
     * @param _imgH New value for member imgH
     */
    eProsima_user_DllExport void imgH(
            int32_t _imgH);

    /*!
     * @brief This function returns the value of member imgH
     * @return Value of member imgH
     */
    eProsima_user_DllExport int32_t imgH() const;

    /*!
     * @brief This function returns a reference to member imgH
     * @return Reference to member imgH
     */
    eProsima_user_DllExport int32_t& imgH();

    /*!
     * @brief This function sets a value in member fpsNum
     * @param _fpsNum New value for member fpsNum
     */
    eProsima_user_DllExport void fpsNum(
            int32_t _fpsNum);

    /*!
     * @brief This function returns the value of member fpsNum
     * @return Value of member fpsNum
     */
    eProsima_user_DllExport int32_t fpsNum() const;

    /*!
     * @brief This function returns a reference to member fpsNum
     * @return Reference to member fpsNum
     */
    eProsima_user_DllExport int32_t& fpsNum();

    /*!
     * @brief This function sets a value in member fpsDen
     * @param _fpsDen New value for member fpsDen
     */
    eProsima_user_DllExport void fpsDen(
            int32_t _fpsDen);

    /*!
     * @brief This function returns the value of member fpsDen
     * @return Value of member fpsDen
     */
    eProsima_user_DllExport int32_t fpsDen() const;

    /*!
     * @brief This function returns a reference to member fpsDen
     * @return Reference to member fpsDen
     */
    eProsima_user_DllExport int32_t& fpsDen();

    /*!
     * @brief This function sets a value in member frmQueSz
     * @param _frmQueSz New value for member frmQueSz
     */
    eProsima_user_DllExport void frmQueSz(
            int32_t _frmQueSz);

    /*!
     * @brief This function returns the value of member frmQueSz
     * @return Value of member frmQueSz
     */
    eProsima_user_DllExport int32_t frmQueSz() const;

    /*!
     * @brief This function returns a reference to member frmQueSz
     * @return Reference to member frmQueSz
     */
    eProsima_user_DllExport int32_t& frmQueSz();

    /*!
     * @brief This function sets a value in member detPyrLev
     * @param _detPyrLev New value for member detPyrLev
     */
    eProsima_user_DllExport void detPyrLev(
            int32_t _detPyrLev);

    /*!
     * @brief This function returns the value of member detPyrLev
     * @return Value of member detPyrLev
     */
    eProsima_user_DllExport int32_t detPyrLev() const;

    /*!
     * @brief This function returns a reference to member detPyrLev
     * @return Reference to member detPyrLev
     */
    eProsima_user_DllExport int32_t& detPyrLev();

    /*!
     * @brief This function sets a value in member detMethodId
     * @param _detMethodId New value for member detMethodId
     */
    eProsima_user_DllExport void detMethodId(
            int32_t _detMethodId);

    /*!
     * @brief This function returns the value of member detMethodId
     * @return Value of member detMethodId
     */
    eProsima_user_DllExport int32_t detMethodId() const;

    /*!
     * @brief This function returns a reference to member detMethodId
     * @return Reference to member detMethodId
     */
    eProsima_user_DllExport int32_t& detMethodId();

    /*!
     * @brief This function sets a value in member detNetworkId
     * @param _detNetworkId New value for member detNetworkId
     */
    eProsima_user_DllExport void detNetworkId(
            int32_t _detNetworkId);

    /*!
     * @brief This function returns the value of member detNetworkId
     * @return Value of member detNetworkId
     */
    eProsima_user_DllExport int32_t detNetworkId() const;

    /*!
     * @brief This function returns a reference to member detNetworkId
     * @return Reference to member detNetworkId
     */
    eProsima_user_DllExport int32_t& detNetworkId();

    /*!
     * @brief This function sets a value in member detFrmsToSkip
     * @param _detFrmsToSkip New value for member detFrmsToSkip
     */
    eProsima_user_DllExport void detFrmsToSkip(
            int32_t _detFrmsToSkip);

    /*!
     * @brief This function returns the value of member detFrmsToSkip
     * @return Value of member detFrmsToSkip
     */
    eProsima_user_DllExport int32_t detFrmsToSkip() const;

    /*!
     * @brief This function returns a reference to member detFrmsToSkip
     * @return Reference to member detFrmsToSkip
     */
    eProsima_user_DllExport int32_t& detFrmsToSkip();

    /*!
     * @brief This function copies the value in member mp4LocationAndPrefix
     * @param _mp4LocationAndPrefix New value to be copied in member mp4LocationAndPrefix
     */
    eProsima_user_DllExport void mp4LocationAndPrefix(
            const std::string& _mp4LocationAndPrefix);

    /*!
     * @brief This function moves the value in member mp4LocationAndPrefix
     * @param _mp4LocationAndPrefix New value to be moved in member mp4LocationAndPrefix
     */
    eProsima_user_DllExport void mp4LocationAndPrefix(
            std::string&& _mp4LocationAndPrefix);

    /*!
     * @brief This function returns a constant reference to member mp4LocationAndPrefix
     * @return Constant reference to member mp4LocationAndPrefix
     */
    eProsima_user_DllExport const std::string& mp4LocationAndPrefix() const;

    /*!
     * @brief This function returns a reference to member mp4LocationAndPrefix
     * @return Reference to member mp4LocationAndPrefix
     */
    eProsima_user_DllExport std::string& mp4LocationAndPrefix();

    /*!
    * @brief This function returns the maximum serialized size of an object
    * depending on the buffer alignment.
    * @param current_alignment Buffer alignment.
    * @return Maximum serialized size.
    */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(
            const UpdateCam& data,
            size_t current_alignment = 0);


    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(
            eprosima::fastcdr::Cdr& cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(
            eprosima::fastcdr::Cdr& cdr);



    /*!
     * @brief This function returns the maximum serialized size of the Key of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(
            eprosima::fastcdr::Cdr& cdr) const;

private:

    std::string m_rtspUrl;
    int32_t m_valid;
    int32_t m_imgW;
    int32_t m_imgH;
    int32_t m_fpsNum;
    int32_t m_fpsDen;
    int32_t m_frmQueSz;
    int32_t m_detPyrLev;
    int32_t m_detMethodId;
    int32_t m_detNetworkId;
    int32_t m_detFrmsToSkip;
    std::string m_mp4LocationAndPrefix;

};

#endif // _FAST_DDS_GENERATED_UPDATECAM_H_

