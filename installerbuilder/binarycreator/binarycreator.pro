TEMPLATE = app
TARGET = binarycreator

DEPENDPATH += . ..
INCLUDEPATH += . .. rcc

DESTDIR = ../bin

CONFIG += console
CONFIG -= app_bundle

include(../libinstaller/libinstaller.pri)

RESOURCES += binarycreator.qrc

# Input
SOURCES = binarycreator.cpp \
          rcc/rcc.cpp \
          rcc/rccmain.cpp \
          ../common/repositorygen.cpp 

HEADERS = rcc/rcc.h

win32:OBJECTS_DIR = .obj
win32:!win32-g++: LIBS += shell32.lib
win32-g++: LIBS += -lshell32
