#-------------------------------------------------
#
# Project created by QtCreator 2011-12-16T14:50:13
#
#-------------------------------------------------

QT       += core gui

TARGET = FractalMaze
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    maze.cpp \
    openmaze.cpp \
    displayarea.cpp \
    tools/CrackMaze/CrackMaze.cpp

HEADERS  += mainwindow.h \
    openmaze.h \
    maze.hpp \
    displayarea.h \
    tools/CrackMaze/CrackMaze.hpp

FORMS    += mainwindow.ui \
    openmaze.ui

RC_FILE += \
    icon.rc










