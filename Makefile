CC=g++
#analyze maze
#LIBSCANMAZE_SRC=scanMaze.cpp util.cpp
SRC2=tools/AnalyzeMaze/AnalyzeMaze.cpp tools/AnalyzeMaze/scanMaze.cpp tools/AnalyzeMaze/util.cpp
#crack maze
CRACKMAZE_SRC= tools/CrackMaze/CrackMazeMain.cpp tools/CrackMaze/CrackMaze.cpp
CPPFLAGS += -O2

#analyze maze
LIBSCANMAZE_OBJ=$(addsuffix .o,$(basename $(LIBSCANMAZE_SRC)))
OBJ1=$(addsuffix .o,$(basename $(SRC1)))
OBJ2=$(addsuffix .o,$(basename $(SRC2)))
#crack maze
CRACKMAZE_OBJ=$(addsuffix .o,$(basename $(CRACKMAZE_SRC)))


TARGET=AnalyzeMaze CrackMaze


ifeq ($(OSNAME), Linux) 
#windows
INC += -I'F:/opencv2.3/build//include'
INC += -I'F:/opencv2.3/build/include/opencv'
#LIBS += -L'C:/opencv/build/x86/mingw/bin' -L.
LIBS += -L'F:/opencv2.3/build/x86/mingw/bin' -L.
#LIBS += -L'C:/opencv-2.3.0/mingw/install/bin'
LIBS += -lopencv_core230 -lopencv_highgui230 -l opencv_imgproc230
else
#linux
INC += -I'/usr/local/include'
LIBS += -L'/usr/local/lib' -L.
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
endif
#
CPPFLAGS+=$(INC)
LDFLAGS+=$(LIBS)

.PHONY: all debug release clean

all:$(TARGET)
	@echo complete

debug:CPPFLAGS += -g
debug:all

release:all

clean:
	-rm -Rf tools/CrackMaze/*.o
	-rm -Rf tools/AnalyzeMaze/*.o
	-rm -Rf CrackMaze*
	-rm -Rf AnalyzeMaze*

AnalyzeMaze:$(OBJ2)
	$(CC) -o $@ $(OBJ2) $(LDFLAGS) $(CPPFLAGS) 

CrackMaze:$(CRACKMAZE_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(CPPFLAGS) 
