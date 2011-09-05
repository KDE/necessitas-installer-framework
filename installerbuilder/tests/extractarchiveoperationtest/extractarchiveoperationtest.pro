TEMPLATE = app
TARGET = extractarchiveoperationtest

DESTDIR = bin

CONFIG -= app_bundle

QT += testlib script
QT -= gui

INCLUDEPATH += ../../libinstaller ..
DEPENDPATH += ../../libinstaller ../../common

include(../../libinstaller/libinstaller.pri)

SOURCES = extractarchiveoperationtest.cpp
HEADERS = extractarchiveoperationtest.h 

win32:!win32-g++: LIBS += ole32.lib oleaut32.lib user32.lib
win32-g++: LIBS += -lole32 -loleaut32 -luser32
win32:OBJECTS_DIR = .obj
