-include Makefile.inc

PROJ_NAME=humidityPub

include Makefile_app_header.mak

#the target binary name
TARGETFILE=$(ODIR_BIN)/humidityPub.out

# link libs
LIBS	:= -lMsg -lCfg -lUtil \
	-lfastrtps -lfastcdr \
	-lboost_timer -lboost_filesystem -lboost_system -lboost_date_time -lboost_regex \
	-lboost_chrono -lboost_thread -pthread \
	-lopencv_ml -lopencv_shape -lopencv_video -lopencv_calib3d \
	-lopencv_highgui -lopencv_videoio -lopencv_flann -lopencv_imgcodecs -lopencv_imgproc -lopencv_core \
	-lv4l2 \
	-ldl -lm -lpthread -lrt 

OBJS = \
	$(ODIR_OBJ)/UpdateHygrometerSubscriber.o \
	$(ODIR_OBJ)/HumidityPublisher.o \
	$(ODIR_OBJ)/mainPub.o 

#	$(ODIR_OBJ)/test_px4_ekf.o \

default:  directories $(TARGETFILE)

directories:    
	mkdir -p $(ODIR_OBJ)
	mkdir -p $(ODIR_LIB)
	mkdir -p $(ODIR_BIN)
	
#the output binary file name is <$(TARGETFILE)>
$(TARGETFILE)	:	$(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) $(LIBS) -o $(TARGETFILE)

$(ODIR_OBJ)/mainPub.o	:	$(SDIR_PROJ)/mainPub.cpp
	$(CXX) -o $(ODIR_OBJ)/mainPub.o $(CFLAGS_EXE) $(SDIR_PROJ)/mainPub.cpp

$(ODIR_OBJ)/HumidityPublisher.o	:	$(SDIR_PROJ)/HumidityPublisher.cpp
	$(CXX) -o $(ODIR_OBJ)/HumidityPublisher.o $(CFLAGS_EXE) $(SDIR_PROJ)/HumidityPublisher.cpp

$(ODIR_OBJ)/UpdateHygrometerSubscriber.o	:	$(SDIR_PROJ)/UpdateHygrometerSubscriber.cpp
	$(CXX) -o $(ODIR_OBJ)/UpdateHygrometerSubscriber.o $(CFLAGS_EXE) $(SDIR_PROJ)/UpdateHygrometerSubscriber.cpp

clean:
	\rm $(ODIR_OBJ)/*.o $(TARGETFILE)

rm_pnt:
	\rm $(TARGETFILE)
            
