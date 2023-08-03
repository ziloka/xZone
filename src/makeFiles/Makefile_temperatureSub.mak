#this Makefile outputs image as a static lib for <PLTF> machine

PROJ_NAME=libTemperatureSub
include Makefile_app_header.mak

# link libs
LIBS	:= -lMsg -lCfg -lUtil \
	-lfastrtps -lfastcdr \
	-lboost_timer -lboost_filesystem -lboost_system -lboost_date_time -lboost_regex \
	-lboost_chrono -lboost_thread -pthread \
	-lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core \
	-lv4l2 \
	-ldl -lm -lpthread -lrt 

OBJS = \
	$(ODIR_OBJ)/UpdateThermometerPublisher.o \
	$(ODIR_OBJ)/TemperatureSubscriber.o

#	$(ODIR_OBJ)/test_px4_ekf.o \

default:  directories $(TARGETFILE)

directories:    
	mkdir -p $(ODIR_OBJ)
	mkdir -p $(ODIR_LIB)
	
#the output lib file name is <$(TARGETFILE)>
$(TARGETFILE)	:	$(OBJS)
	ar rcs $(TARGETFILE) $(OBJS)

$(ODIR_OBJ)/TemperatureSubscriber.o	:	$(SDIR_PROJ)/TemperatureSubscriber.cpp
	$(CXX) -o $(ODIR_OBJ)/TemperatureSubscriber.o $(CFLAGS_EXE) $(SDIR_PROJ)/TemperatureSubscriber.cpp

$(ODIR_OBJ)/UpdateThermometerPublisher.o	:	$(SDIR_PROJ)/UpdateThermometerPublisher.cpp
	$(CXX) -o $(ODIR_OBJ)/UpdateThermometerPublisher.o $(CFLAGS_EXE) $(SDIR_PROJ)/UpdateThermometerPublisher.cpp

clean:
	\rm $(ODIR_OBJ)/*.o $(TARGETFILE)

rm_pnt:
	\rm $(TARGETFILE)
            
