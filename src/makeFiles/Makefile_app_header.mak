-include Makefile.inc

#----------------------------------------------------------
# env variables need to defined in /home/nvidia/.bashrc 
#
# export XZONE_ROOT=/home/projects/xZone
# export CUDA_INC=/usr/local/cuda-10.0/targets/aarch64-linux/include
# export CUDA_LIB=/usr/local/cuda-10.0/targets/aarch64-linux/lib

# Instead of letting the developer manually say where their project is located why not use pwd, a built in shell command? (type "type pwd" to prove it is built in)

XZONE_ROOT=$(shell pwd)/../../

# build intermediate output paths
SDIR_ROOT=$(XZONE_ROOT)/src
SDIR_PROJ=$(XZONE_ROOT)/src/$(PROJ_NAME)

$(info $(XZONE_ROOT))

ODIR_ROOT=$(XZONE_ROOT)/build
ODIR_OBJ=$(ODIR_ROOT)/$(PROJ_NAME)
ODIR_LIB=$(ODIR_ROOT)/libs
ODIR_BIN=$(ODIR_ROOT)/bin

# include and lib paths of the platform
PLTF_INC=/usr/include
PLTF_LIB=/usr/lib
BOOST_INC=/usr/include
BOOST_LIB=/usr/lib

CV_INC=/usr/local/include/opencv4
CV_LIB=/usr/local/lib

DDS_INC=/usr/local/include
DDS_LIB=/usr/local/lib

# GST_INC=-I/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/aarch64-linux-gnu/glib-2.0/include
# GST_LIB=/usr/lib/aarch64-linux-gnu/gstreamer-1.0

CC = /usr/bin/gcc
CXX = /usr/bin/g++

#DEBUG = -g
DEBUG = -DNDEBUG -g
#DEBUG = -DDEBUG -g

#include flags for building libs
CFLAGS = -Wall -static -c $(DEBUG) -DECL_STANDALONE=1 -DqDNGDebug=1 -D__xlC__=1 -DNO_FCGI_DEFINES=1 -DqDNGUseStdInt=0 -DUNIX_ENV=1 -D__LITTLE_ENDIAN__=1 -DqMacOS=0 -DqWinOS=0 -std=gnu++14 \
	-I$(SDIR_PROJ) -I$(SDIR_ROOT) -I$(DDS_INC) -I$(CV_INC) -I$(BOOST_INC) -I$(PLTF_INC)

#include flags for building executable
CFLAGS_EXE	:= -Wall -c $(DEBUG) -DECL_STANDALONE=1 -DqDNGDebug=1 -D__xlC__=1 -DNO_FCGI_DEFINES=1 -DqDNGUseStdInt=0 -DUNIX_ENV=1 -D__LITTLE_ENDIAN__=1 -DqMacOS=0 -DqWinOS=0 -std=gnu++14 \
	-I$(SDIR_PROJ) -I$(SDIR_ROOT) -I$(DDS_INC) -I$(CV_INC) -I$(BOOST_INC) -I$(PLTF_INC)

#link flags and lib searching paths
LFLAGS	:= -Wall $(DEBUG) -L$(ODIR_LIB) -L$(CV_LIB) -L$(DDS_LIB) -L$(BOOST_LIB) -L/usr/lib/x86_64-linux-gnu -L$(PLTF_LIB) 

TARGETFILE=$(ODIR_LIB)/$(PROJ_NAME).a

