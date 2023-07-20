## How to build from source

Note: *C++17 and above is required*

### Windows 10 & __**visual studio 2019**__


#### Requirements
- Visual Studio 2019 version 16.0.0 
- [Chocolately](https://fast-dds.docs.eprosima.com/en/latest/installation/sources/sources_windows.html#chocolatey-sw)

~~Note: I wrote this on Visual Studio Community 2022 64-bit Version 17.4.5~~

1. open "x64 native tools command prompt" (install visual studio first, ensure c++ development tools are installed)

2. Acquire and build dependencies

	1. Compile the gtest library

		3. Compile 
			```pwsh
			git clone --jobs 4 --depth=1 --single-branch --branch v1.13.0 --recursive https://github.com/google/googletest
			mkdir vs2019-install
			cd vs2019-install
			cmake -G "Visual Studio 16 2019" -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug -DCMAKE_DEBUG_POSTFIX=d -DBUILD_SHARED_LIBS=ON ..
			cmake --build . --parallel 4 --config debug
			```
			Notes:
			- https://stackoverflow.com/questions/59620509/set-msvc-runtime-on-cmake-project-from-command-line
			- https://github.com/google/googletest/issues/449

	2. Install gstreamer runtime and development packages
		
		1. Set up the environment variables
			- [MSVC 64-bit (VS 2019, Release CRT) 1.22.4 runtime installer](https://gstreamer.freedesktop.org/data/pkg/windows/1.22.4/msvc/gstreamer-1.0-msvc-x86_64-1.22.4.msi)
			- [MSVC 64-bit (VS 2019, Release CRT) 1.22.4 development installer](https://gstreamer.freedesktop.org/data/pkg/windows/1.22.4/msvc/gstreamer-1.0-devel-msvc-x86_64-1.22.4.msi)

		2. 

	3. Install the opencv library

		1. Compile it

		```pwsh
		mkdir opencv
		cd opencv
		git clone --jobs 4 --depth=1 --single-branch --branch 4.1.1 --recursive https://github.com/opencv/opencv
		git clone --jobs 4 --depth=1 --single-branch --branch 4.1.1 --recursive https://github.com/opencv/opencv_contrib
		mkdir build
		cd build
		cmake -G "Visual Studio 16 2019" -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DBUILD_DOCS=OFF -DWITH_CUDA=OFF -DBUILD_EXAMPLES=OFF -DINSTALL_CREATE_DISTRIB=ON -DWITH_GSTREAMER=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules -DBUILD_SHARED_LIBS=ON ../opencv
		cmake --build . --parallel 4 --target install --config debug
		```
		opencv lib is located in ./install/$(arch)/$(MSVC_VER)/lib
		opencv include is located in ./install/include
		[extra info](https://github.com/shunguang/HowTo/blob/master/build-opencv/how-to-build-cv-w-contrib-modules-4-VS.txt)

		Shortcut:
		```pwsh
		vcpkg install opencv[gstreamer,ffmpeg,python]:x64-windows
		```

	4. Compile the boost library

		1. Get source code, configure, and compile
		```sh
		git clone --jobs 4 --depth=1 --single-branch --branch boost-1.71.0 --recursive https://github.com/boostorg/boost
		cd boost
		.\bootstrap
		.\b2
		```
		**Boost Libraries are located at stage/lib**

		*Notes*:
		~~- use `.\b2 --build-dir=build/x64 address-model=64 threading=multi --build-type=complete --stagedir=./stage/x64` libs are located in **stage/x64**~~
		- https://stackoverflow.com/questions/302208/how-do-you-build-the-x64-boost-libraries-on-windows
		- https://stackoverflow.com/questions/2049952/how-to-get-boost-libraries-binaries-that-work-with-visual-studio
		- https://stackoverflow.com/questions/13042561/fatal-error-lnk1104-cannot-open-file-libboost-system-vc110-mt-gd-1-51-lib
		- https://stackoverflow.com/questions/6014517/whats-the-difference-between-mt-gd-and-mt-s-library
		- Faster alternative: https://boost.teeks99.com/, http://sourceforge.net/projects/boost/files/boost-binaries/
		- https://anaconda.org/conda-forge/boost

	5. Installing the fast dds library

		1. go to https://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-dds/eprosima-fast-dds-2-9-1/eprosima_fast-dds-2-9-1-windows-exe?format=raw

		2. run executable

<!-- ```pwsh
mkdir Fast-DDS
cd Fast-DDS
git clone https://github.com/eProsima/foonathan_memory_vendor.git
cd foonathan_memory_vendor
mkdir build
cd build
# This library needs to compile shared libraries
cmake -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebugDLL -DCMAKE_INSTALL_PREFIX:FILEPATH=../../install -DBUILD_SHARED_LIBS=ON ..
cmake --build . --parallel 4 --target install --config debug
cd ../..

git clone https://github.com/eProsima/Fast-CDR.git
cd Fast-CDR
mkdir build
cd build
cmake -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebugDLL -DCMAKE_INSTALL_PREFIX:FILEPATH=../../install -DBUILD_SHARED_LIBS=ON ..
cmake --build . --parallel 4 --target install --config debug
cd ../..

git clone --jobs 4 --depth=1 --single-branch --branch 2.9.1 --recursive https://github.com/eProsima/Fast-DDS
cd Fast-DDS
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebugDLL -DCMAKE_INSTALL_PREFIX:FILEPATH=../../install -DBUILD_SHARED_LIBS=ON -DTHIRDPARTY=ON ..
# this actually doesn't make cmake have multiple jobs in this project
cmake --build . --parallel 4 --target install --config debug
``` -->
		Notes:
		- required to build this from source instead of just downloading a executable and running that because runtime library must be multithreadeddebug
		- https://fast-dds.docs.eprosima.com/en/latest/installation/sources/sources_windows.html#cmake-installation
		- https://stackoverflow.com/questions/11840482/cmake-install-prefix-environment-variable-doesnt-work
		- [CMAKE_INSTALL_PREFIX with relative paths behaves differently with and without FILEPATH](https://gitlab.kitware.com/cmake/cmake/-/issues/16445)
		- https://github.com/eProsima/Fast-DDS/issues/2275#issuecomment-946429816
		- https://github.com/eProsima/Fast-DDS/issues/107#issuecomment-303091369 (USE THIRDPARTY=ON)
		- https://github.com/eProsima/Fast-DDS/blob/e96f0828759ec6c5def1338b1244ac9c534f1854/CMakeLists.txt#L223-L233
		- https://cmake.org/cmake/help/latest/variable/BUILD_SHARED_LIBS.html
		- https://cmake.org/cmake/help/v3.0/variable/CMAKE_INSTALL_PREFIX.html
		- [Fast-RTPS no longer builds due to non-standard install location for dependency foonathan_memory [6117]](https://github.com/eProsima/Fast-DDS/issues/620)
		- [Including FastRTPS in Qt Projects: LNK2005 already defined [8982]](https://github.com/eProsima/Fast-DDS/issues/904)
		- I'm assuming fast dds libraries are shared if they start with lib and static if they don't according to [this](https://stackoverflow.com/questions/10549669/linking-to-boost-libraries-fails-because-of-lib-prefix) logic
		- Project must use dynamic linking of some sort according to [this](https://stackoverflow.com/questions/9527713/mixing-a-dll-boost-library-with-a-static-runtime-is-a-really-bad-idea) 
		- [Including FastRTPS in Qt Projects: LNK2005 already defined [8982]](https://github.com/eProsima/Fast-DDS/issues/904#issuecomment-561022760)
		- [Build Fail with "fatal error LNK1169: one or more multiply defined symbols found"](https://github.com/google/jax/issues/14165)
		- [libfastrtps-2.7.lib(Time_t.obj)👎 error: LNK2005: "public: __thiscall eprosima::fastrtps::Time_t::Time_t(int,unsigned int)" (??0Time_t@fastrtps@eprosima@@QAE@HI@Z)ist bereits in fastrtps-2.7.lib(fastrtps-2.7.dll) definiert. [17537]](https://github.com/eProsima/Fast-DDS/issues/3330)

3. copy \$(XZONE_SRC)/vs2019/open_xZone_vs2019_template.bat to $(XZONE_SRC)/vs2019/open_xZone_vs2019_xyz.bat

4. edit $(XZONE_SRC)/vs2019/open_xZone_vs2019_xyz.bat to make sure the path is corresponding to your envrionment

5. look at ./src/libMsg/how-to-run-fastgen.txt before attempting to compile

	C:\pkg\fastDDS\bin\fastddsgen .\idl\Image.idl

6. **configure projects to be compiled in the correct order**

7. double click $(XZONE_SRC)/vs2019/open_xZone_vs2019_xyz.bat

8. troubleshooting tips
- Try cleaning solution
	In the upper left corner click **Build** ` Build -> Clean Solution`
- Unresolved external symbol errors?
	In the solution explorer, right click and click on properties on the project that the error came from. Go to `Configuration Properties -> Linker -> Input`. Edit the Additional Dependencies field and add "$(APP_LIBS_R)"
- mismatch detected for 'RuntimeLibrary': value 'x' doesn't match value 'y'.
	In the solution explorer, right click and click on properties on the project that the error came from. Go to `Configuration Properties -> C/C++ -> Code Generation`. Change the Runtime Library so the value is the same as the x value
	Another solution is to change the solution configurations
- All subproject's runtime library should be set to `Multi-threaded Debug DLL (/MDd)`,
	Except the test subproject, should be set to `Multi-threaded (/MT)` instead
- unresolved external symbol "_invalid_parameter, _calloc_dbg, _free_dbg, _malloc_dbg, etc ..." ?
	In the upper left corner change Solution Configuration to `Debug`
- Random unresolved symbols? 
	Try looking through [this](https://github.com/eProsima/Fast-DDS/issues/2805)
- Look at [demo project](https://github.com/eProsima/Fast-DDS-docs/tree/master/code/Examples/C%2B%2B/DDSHelloWorld) (Do this in development command prompt)
	- [Tutorial](https://fast-dds.docs.eprosima.com/en/latest/fastdds/getting_started/simple_app/simple_app.html)
	git clone --no-checkout https://github.com/eProsima/Fast-DDS-docs
	cd Fast-DDS-Docs
	git sparse-checkout init --cone
	git sparse-checkout set code/Examples/C++/DDSHelloWorld
	git checkout "@"
	cd code/Examples/C++/DDSHelloWorld
	mkdir build
	cd build
	cmake ..
	cmake --build .
- Trying to execute fastPubEx1.exe but it retursn `cannot find opencv_world411d.dll` ?
	Copy the opencv_world411d.dll from $(PKG)/opencv/build/install/x64/vc16/bin to the same directory as the fastPubEx1.exe executable
- cv::impl::DynamicLib::libraryLoad load opencv_videoio_gstreamer411_64.dll => FAILED?
	Copy the opencv_videoio_ffmpeg411_64.dll from $(PKG)/opencv/build/install/x64/vc16/bin to the same directory as the fastPubEx1.exe executable

### linux

1. set up dependencies
	#### Ubuntu 20.04
	1. Install prebuilt dependencies of the latest version

	```bash
	sudo apt update && sudo apt install -y cmake g++ wget unzip
	sudo apt-get install googletest libboost-dev
	# Kinda not really required for opencv contrib
	sudo apt-get install ccache libopencv-dev lib32z1 libopenjp2-7-dev libopenexr-dev libva-dev libopenblas-dev libatlas3-base libopenblas-dev liblapack-dev libjna-jni libvtk7-dev libgtk-3-0 libgstreamer1.0-dev libeigen3-dev libharfbuzz-dev libhdf5-dev libjulia-openblas64 libgflags-dev libgoogle-glog-dev libtesseract-dev glogg libv4l-dev
	```

	2. Compile the boost library

	```bash
	wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz
	tar xf boost_1_80_0.tar.gz
	cd boost_1_80_0
	./bootstrap.sh --prefix=/usr/
	sudo ./b2 install -j 4
	```
	Notes:
		- https://stackoverflow.com/questions/33566782/building-all-of-boost-in-a-few-minutes

	3. Compile the OpenCV library 
	
	~~wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
	wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
	unzip -q opencv.zip
	unzip -q opencv_contrib.zip~~

	```bash
	mkdir opencv
	cd opencv
	git clone --jobs 4 --depth=1 --single-branch --branch 4.1.1 --recursive https://github.com/opencv/opencv
	git clone --jobs 4 --depth=1 --single-branch --branch 4.1.1 --recursive https://github.com/opencv/opencv_contrib
	mkdir -p build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_PERF_TESTS:BOOL=OFF -DBUILD_TESTS:BOOL=OFF -DBUILD_DOCS:BOOL=OFF -DWITH_CUDA:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DINSTALL_CREATE_DISTRIB=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ../opencv
	make -j8
	sudo make install
	# Or use ninja instead, parallel builds automatically
	# cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_PERF_TESTS:BOOL=OFF -DBUILD_TESTS:BOOL=OFF -DBUILD_DOCS:BOOL=OFF -DWITH_CUDA:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DINSTALL_CREATE_DISTRIB=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ../opencv 
	# cmake --build . --parallel 4
	```
	*Note*: This is specifically suppose to be for opencv 4.1.1.
	- [The ultimate OpenCV cross compilation guide for embedded processors](https://medium.com/analytics-vidhya/the-ultimate-opencv-cross-compilation-guide-for-embedded-processors-f2fdc8ccb7b2)

	Opencv headers (include) are located at `/usr/local/include/opencv4`
	Opencv libraries are located at `/usr/local/lib`

	If Opencv files aren't located there you can try finding where they are located via 
	```bash
	dpkg -L libopencv-dev
	# the following is also worth a shot
	pkg-config --libs --cflags opencv4
	```

	4. Compile the fastDDS library
	
		Any Unix / Linux platform probably requires to install FastDDS in the following

		1. Download source code here https://github.com/eProsima/Fast-DDS/tree/2.9.1
		
		2. Extract file

		3. Install it
		```bash
		sudo ./install.sh
		```

		So the following should be the process of installing fast DDS
		```bash
		git clone --jobs 4 --depth=1 --single-branch --branch=2.9.1 --recursive https://github.com/eProsima/Fast-DDS fastDDS
		sudo ./install.sh
		# Alternative
		# mkdir fastDDS
		# cd fastDDS
		# wget -O eProsima_Fast-DDS-v2.9.1-Linux.tgz https://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-dds/eprosima-fast-dds-2-9-1/eprosima_fast-dds-v2-9-1-linux-tgz?format=raw
		# tar xzf eProsima_Fast-DDS-v2.9.1-Linux.tgz
		# sudo ./install.sh
		```

		4. The library is now located at /usr/local/lib

2. set environment variables PKG and XZONE_SRC 

3. cd $(XZONE_SRC)/makeFiles execute 

4. ./run_all_wo_cleanAll.sh

5. (you may (probably will) need to to edit Makefile_app_header.mak if there is any errors)	  

Troubleshooting
---------------
- Running into issues trying to run the script on linux? ("/bin/bash^M: bad interpreter: No such file or directory") 
	remove carriage return characters
	```
	sed -i -e 's/\r$//' ./run_all_wo_cleanAll.sh
	```