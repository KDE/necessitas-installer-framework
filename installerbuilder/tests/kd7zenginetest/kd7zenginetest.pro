TEMPLATE = app
TARGET = kd7zenginetest

DESTDIR = bin

CONFIG -= app_bundle

QT += testlib

include(../../libinstaller/libinstaller.pri)

SOURCES = kd7zenginetest.cpp 
HEADERS = kd7zenginetest.h 

win32:!win32-g++: LIBS += ole32.lib oleaut32.lib user32.lib
win32-g++: LIBS += -lole32 -loleaut32 -luser32
win32:OBJECTS_DIR = .obj
