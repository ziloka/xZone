# xZone 
an open source project for monitoring and controling multiple sensors in a centralized way
(03/26/2023)

## PGK and SRC dir
	(a) for windows
		PKG=c:\pkg
		XZONE_SRC=C:\Users\wus1\Projects\xZone\src
	(b) for linux
		PKG=~\pkg
		XZONE_SRC=~\xZone\src
	
## Dependency
    a) gtest
      GTEST_INC=$(PKG)\googletest\vs2019-install\include
	  GTEST_LIB=$(PKG)\googletest\vs2019-install\lib
	  
    b) opencv
		CV_INC=$(PKG)\opencv\opencv-4.1.1\install-local-w-contrib-vc2019-x64\include
		CV_LIB=$(PKG)\opencv\opencv-4.1.1\install-local-w-contrib-vc2019-x64\x64\vc16\lib
	
	c) boost
		BOOST_INC=$(PKG)\boost\boost_1_71_0
		BOOST_LIB=$(PKG)\boost\boost_1_71_0\lib64-msvc-14.2
		
	d) fast DDS
		DDS_INC=$(PKG)\fastDDS\v2.9.1\include
		DDS_LIB=$(PKG)\fastDDS\v2.9.1\lib\x64Win64VS2019


# Getting started

After compiling the application you must write a configuration file see [Configuration.md](CONFIGURATION.md) for details

# Building from source

see [BUILD_FROM_SOURCE.md](BUILD_FROM_SOURCE.md)

[https://github.com/shunguang/HowTo/blob/master/set-imx8-env-AIO.txt](here) and [https://github.com/shunguang/HowTo/tree/master/solidRun](here)