git clone --jobs 4 --depth=1 --single-branch --branch v1.13.0 --recursive https://github.com/google/googletest
cd googletest
mkdir vs2019-install
cd vs2019-install
cmake -G "Visual Studio 16 2019" -D CMAKE_DEBUG_POSTFIX=d -D BUILD_SHARED_LIBS=ON ..
cmake --build . --parallel 4 --config debug
cmake --build . --parallel 4 --config release

cd ../..

mkdir opencv
cd opencv
git clone --jobs 4 --depth=1 --single-branch --branch 4.1.1 --recursive https://github.com/opencv/opencv
git clone --jobs 4 --depth=1 --single-branch --branch 4.1.1 --recursive https://github.com/opencv/opencv_contrib
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D BUILD_DOCS=OFF -D WITH_CUDA=OFF -D BUILD_EXAMPLES=OFF -D INSTALL_CREATE_DISTRIB=ON -D WITH_GSTREAMER=ON -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules -D BUILD_opencv_world=ON -D BUILD_SHARED_LIBS=ON ../opencv
cmake --build . --parallel 4 --target install --config debug
cmake --build . --parallel 4 --target install --config release

cd ../..

git clone --jobs 4 --depth=1 --single-branch --branch boost-1.71.0 --recursive https://github.com/boostorg/boost
cd boost
.\bootstrap
.\b2

cd ..

mkdir Fast-DDS
cd Fast-DDS
git clone --jobs 4 --depth=1 --single-branch https://github.com/eProsima/foonathan_memory_vendor.git
cd foonathan_memory_vendor
mkdir build
cd build
# This library needs to compile shared libraries
cmake -G "Visual Studio 16 2019" -D CMAKE_INSTALL_PREFIX:FILEPATH=../../install -D BUILD_SHARED_LIBS=ON ..
cmake --build . --parallel 4 --target install --config debug
cmake --build . --parallel 4 --target install --config release
# this command is probably needed to merge it because the install prefix is incorrect somehow
xcopy /E ..\..\..\install\*.* ..\..\install

git clone --jobs 4 --depth=1 --single-branch --branch 1.0.x https://github.com/eProsima/Fast-CDR.git fast-cdr-1.0.x
cd fast-cdr-1.0.x
mkdir build
cd build
# files with no lib prefixes
cmake -G "Visual Studio 16 2019" -D CMAKE_INSTALL_PREFIX:FILEPATH=../../install -D BUILD_SHARED_LIBS=ON ..
cmake --build . --parallel 4 --target install --config debug
cmake --build . --parallel 4 --target install --config release
# Have the files starting with lib prefixes

# for release, the wanted dep is in the install/bin folder
git clone --jobs 4 --depth=1 --single-branch https://github.com/eProsima/Fast-CDR.git
cd Fast-CDR
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -D CMAKE_INSTALL_PREFIX:FILEPATH=../../install -D BUILD_SHARED_LIBS=ON ..
cmake --build . --parallel 4 --target install --config release

cd ../..

git clone --jobs 4 --depth=1 --single-branch --branch 2.12.1 --recursive https://github.com/eProsima/Fast-DDS
cd Fast-DDS
mkdir build
cd build
# If this command doesn't work try setting the absolute path and trying again
set CMAKE_PREFIX_PATH=../../install/share/foonathan_memory/cmake
cmake -G "Visual Studio 16 2019" -D CMAKE_INSTALL_PREFIX:FILEPATH=../../install -D BUILD_SHARED_LIBS=ON -D THIRDPARTY=ON -D STRICT_REALTIME=ON -D foonathan_memory_DIR=../../install/share/foonathan_memory/cmake ..
# this actually doesn't make cmake have multiple jobs in this project
cmake --build . --parallel 4 --target install --config debug
cmake --build . --parallel 4 --target install --config release

git clone --recursive --depth=1 --single-branch --branch v2.5.1 https://github.com/eProsima/Fast-DDS-Gen.git
cd Fast-DDS-Gen
.\gradlew.bat assemble