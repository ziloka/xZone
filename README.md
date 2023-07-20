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
	
## How to build from source

Note: *C++17 and above is required*

### Windows __**visual studio 2019 and upper**__

1. Acquire and build dependencies
	1. Compile the gtest library

		1. clone repository https://github.com/google/googletest/releases

		2. open "x64 native tools command prompt" (install visual studio first, ensure c++ development tools are installed)

		3. Compile 
			```
			mkdir vs2019-install && cd vs2019-install
			cmake -G "NMake Makefiles" ..
			nmake
			```

	2. Install the opencv library

		1. go to https://sourceforge.net/projects/opencvlibrary/files/4.1.1/opencv-4.1.1-vc14_vc15.exe/download

		2. run the executable

	3. Compile the boost library
		1. Get source code

		```
		git clone --recursive --depth=1 -j8 https://github.com/boostorg/boost
		cd boost
		```
		
		Note: *afb333b7c5101041f0280b2edf155c55114c9c95* is the last commit to boost library version 1.71.0
		Run the following commands if the library doesn't seem compatible
		```
		git clone -n https://github.com/boostorg/boost
		cd boost
		git checkout afb333b7c5101041f0280b2edf155c55114c9c95
		```
		1. Compile
		```sh
		.\bootstrap
		.\b2
		```
		*Notes*:
		- use `.\b2 --build-dir=build/x64 address-model=64 threading=multi --build-type=complete --stagedir=./stage/x64` 
		instead of step 3 for 64 bit boost library
		- https://stackoverflow.com/questions/302208/how-do-you-build-the-x64-boost-libraries-on-windows
		- https://stackoverflow.com/questions/2049952/how-to-get-boost-libraries-binaries-that-work-with-visual-studio
		- Faster alternative: https://boost.teeks99.com/, http://sourceforge.net/projects/boost/files/boost-binaries/
		- https://anaconda.org/conda-forge/boost

	4. Installing the fast dds library

		1. go to https://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-dds/eprosima-fast-dds-2-9-1/eprosima_fast-dds-2-9-1-windows-exe?format=raw

		2. run executable

1. copy \$(XZONE_SRC)/vs2019/open_xZone_vs2019_template.bat to $(XZONE_SRC)/vs2019/open_xZone_vs2019_xyz.bat

2. edit $(XZONE_SRC)/vs2019/open_xZone_vs2019_xyz.bat to make sure the path is corresponding to your envrionment

3. look at ./src/libMsg/how-to-run-fastgen.txt before attempting to compile

	C:\pkg\fastDDS\bin\fastddsgen -ppDisable .\idl\MsgTmp.idl

4. **configure projects to be compiled in the correct order**

5. double click $(XZONE_SRC)/vs2019/open_xZone_vs2019_xyz.bat

### linux

1. set up dependencies
	#### Ubuntu 20.04
	Install prebuilt dependencies of the latest version
	```bash
	sudo apt update && sudo apt install -y cmake g++ wget unzip
	sudo apt-get install googletest libboost-dev
	# Kinda not really required for opencv contrib
	sudo apt-get install ccache libopencv-dev
	# More dependencies that may be used in the future
	# lib32z1 libopenjp2-7-dev libopenexr-dev libva-dev libopenblas-dev libatlas3-base libopenblas-dev liblapack-dev libjna-jni libvtk7-dev libgtk-3-0 libgstreamer1.0-dev libeigen3-dev libharfbuzz-dev libhdf5-dev libjulia-openblas64 libgflags-dev libgoogle-glog-dev libtesseract-dev glogg
	```
<!-- 
	~~wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
	wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
	unzip -q opencv.zip
	unzip -q opencv_contrib.zip~~

	Building OpenCV from source
	```
	mkdir opencv
	cd opencv
	git clone --jobs 4 --depth=1 --branch 4.x --recursive https://github.com/opencv/opencv
	git clone --jobs 4 --depth=1 --branch 4.x --recursive https://github.com/opencv/opencv_contrib
	mkdir -p build && cd build
	cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ../opencv
	cmake --build .
	``` -->

	Opencv headers (include) are located at 
	Opencv libraries by default are located at `/usr/include/opencv4`

	If Opencv files aren't located there you can try finding where they are located via 
	```
	dpkg -L libopencv-dev
	```

	I believe only Ubuntu is able to install FastDDS in the following without modifying the script at all

	1. Download source code here https://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-dds/eprosima-fast-dds-2-9-1/eprosima_fast-dds-v2-9-1-linux-tgz?format=raw
	
	2. Extract file

	3. Install it
	```
	sudo ./install.sh
	```

	So the following should be the process of installing fast DDS
	```bash
	mkdir fastDDS
	wget -O eProsima_Fast-DDS-v2.9.1-Linux.tgz https://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-dds/eprosima-fast-dds-2-9-1/eprosima_fast-dds-v2-9-1-linux-tgz?format=raw
	tar xzf eProsima_Fast-DDS-v2.9.1-Linux.tgz
	sudo ./install.sh --no-static-libs
	```
	Looking at ./devcontainer/Dockerfile should give you a rough idea of how it should be set up

	4. The library is now located at /usr/local/lib

2. set environment variables PKG and XZONE_SRC 

3. cd $(XZONE_SRC)/makeFiles execute 

4. ./run_all_w_cleanAll.sh 

5. (you may need to to edit Makefile_app_header.mak if there is any errors)	  
