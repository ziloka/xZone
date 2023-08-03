#this Makefile outputs image as a static lib for <PLTF> machine

PROJ_NAME=libImageSub
include Makefile_app_header.mak

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
	$(ODIR_OBJ)/UpdateCamPublisher.o \
	$(ODIR_OBJ)/ImageSubscriber.o

#	$(ODIR_OBJ)/test_px4_ekf.o \

default:  directories $(TARGETFILE)

directories:    
	mkdir -p $(ODIR_OBJ)
	mkdir -p $(ODIR_LIB)
	
#the output lib file name is <$(TARGETFILE)>
$(TARGETFILE)	:	$(OBJS)
	ar rcs $(TARGETFILE) $(OBJS)

$(ODIR_OBJ)/ImageSubscriber.o	:	$(SDIR_PROJ)/ImageSubscriber.cpp
	$(CXX) -o $(ODIR_OBJ)/ImageSubscriber.o $(CFLAGS_EXE) $(SDIR_PROJ)/ImageSubscriber.cpp

$(ODIR_OBJ)/UpdateCamPublisher.o	:	$(SDIR_PROJ)/UpdateCamPublisher.cpp
	$(CXX) -o $(ODIR_OBJ)/UpdateCamPublisher.o $(CFLAGS_EXE) $(SDIR_PROJ)/UpdateCamPublisher.cpp

clean:
	\rm $(ODIR_OBJ)/*.o $(TARGETFILE)

rm_pnt:
	\rm $(TARGETFILE)
            
