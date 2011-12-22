CC=g++
#analyze maze
#LIBSCANMAZE_SRC=scanMaze.cpp util.cpp
#SRC1=AnalyzeMazeTest.cpp
SRC2=AnalyzeMaze/AnalyzeMaze.cpp AnalyzeMaze/scanMaze.cpp AnalyzeMaze/util.cpp
#crack maze
CRACKMAZE_SRC= CrackMaze/CrackMazeMain.cpp CrackMaze/CrackMaze.cpp
CPPFLAGS += -O2

#analyze maze
LIBSCANMAZE_OBJ=$(addsuffix .o,$(basename $(LIBSCANMAZE_SRC)))
OBJ1=$(addsuffix .o,$(basename $(SRC1)))
OBJ2=$(addsuffix .o,$(basename $(SRC2)))
#crack maze
CRACKMAZE_OBJ=$(addsuffix .o,$(basename $(CRACKMAZE_SRC)))


TARGET=AnalyzeMaze CrackMaze


#opencv
#ifdef opencv
INC += -I'C:/opencv2.3/build//include'
INC += -I'C:/opencv2.3/build/include/opencv'
#LIBS += -L'C:/opencv/build/x86/mingw/bin' -L.
LIBS += -L'C:/opencv2.3/build/x86/mingw/bin' -L.
#LIBS += -L'C:/opencv-2.3.0/mingw/install/bin'
LIBS += -lopencv_core230 -lopencv_highgui230 -l opencv_imgproc230 -lopencv_contrib230
LIBS += -lopencv_features2d230 -lopencv_flann230 -lopencv_gpu230 -lopencv_legacy230
LIBS += -lopencv_ml230 -lopencv_objdetect230 -lopencv_video230 
LIBS += -lopencv_calib3d230
#endif
CPPFLAGS+=$(INC)
LDFLAGS+=$(LIBS)

.PHONY: all debug release clean

all:$(TARGET)
	@echo complete

debug:CPPFLAGS += -g
debug:all

release:all

clean:
	-rm -Rf CrackMaze/*.o
	-rm -Rf AnalyzeMaze/*.o
	-rm -Rf *.exe

#libscanmaze.dll:$(LIBSCANMAZE_OBJ)
#	$(CC) -shared -fPIC -o $@ $^ $(CPPFLAGS) $(LIBS)

#AnalyzeMazeTest:libscanmaze.dll $(OBJ1)
#	$(CC) -o $@ $(OBJ1) $(LDFLAGS) $(CPPFLAGS) -lscanmaze

AnalyzeMaze:$(OBJ2)
	$(CC) -o $@ $(OBJ2) $(LDFLAGS) $(CPPFLAGS) 

CrackMaze:$(CRACKMAZE_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(CPPFLAGS) 
