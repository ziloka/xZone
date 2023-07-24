#!/bin/bash

#clean all
make -f Makefile_util.mak clean
make -f Makefile_msg.mak clean
make -f Makefile_cfg.mak clean
make -f Makefile_humidityPub.mak clean
make -f Makefile_humiditySub.mak clean
make -f Makefile_imagePub.mak  clean
make -f Makefile_imageSub.mak  clean
make -f Makefile_temperaturePub.mak clean
make -f Makefile_temperatureSub.mak clean
make -f Makefile_test.mak  clean

#---------------------------------------

make -f Makefile_util.mak -j4
make -f Makefile_msg.mak  -j4
make -f Makefile_cfg.mak -j4
make -f Makefile_humidityPub.mak -j4
make -f Makefile_humiditySub.mak -j4
make -f Makefile_imagePub.mak -j4
make -f Makefile_imageSub.mak -j4
make -f Makefile_temperaturePub.mak -j4
make -f Makefile_temperatureSub.mak -j4
make -f Makefile_test.mak -j4
#---eof---

