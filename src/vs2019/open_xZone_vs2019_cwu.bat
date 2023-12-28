@echo off

REM define environment variables, do not change the variable name, just it's value!
set GTEST_INC=D:\pkg\googletest\googletest\include\gtest
set GTEST_LIB=D:\pkg\googletest\vs2019-install\lib\Release

set CV_INC=D:\pkg\opencv\build\install\include
set CV_LIB=D:\pkg\opencv\build\install\x64\vc16\lib

set BOOST_INC=D:\pkg\boost\boost_1_71_0
set BOOST_LIB=D:\pkg\boost\boost_1_71_0\stage\lib

@REM set DDS_INC=C:\Program Files\eProsima\fastrtps 2.9.1\include
@REM set DDS_LIB=C:\Program Files\eProsima\fastrtps 2.9.1\lib\x64Win64VS2019

set DDS_INC=C:\Program Files\eProsima\fastrtps 2.12.1\include
set DDS_LIB=C:\Program Files\eProsima\fastrtps 2.12.1\lib\x64Win64VS2019
@REM set DDS_INC=D:\pkg\Fast-DDS\install\include
@REM set DDS_LIB=D:\pkg\Fast-DDS\install\lib

set APP_SRC=C:\Users\conno\Documents\xZone\src
set APP_BUILD_INT=C:\Users\conno\Documents\xZone\build-vs2019-x64\int
set APP_BUILD_BIN=C:\Users\conno\Documents\xZone\build-vs2019-x64\bin

devenv %APP_SRC%\vs2019\xZone_vs2019.sln

REM ---eof---/Users/wus1/Projects/2020/p803/software/payload-cpu/pyxis-analysis/vs2017/pyxisAnalysis.props
