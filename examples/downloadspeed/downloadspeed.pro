include(../../installerbuilder/libinstaller/libinstaller.pri)
DEPENDPATH += ../../installerbuilder/libinstaller ../../installerbuilder/common
INCLUDEPATH += ../../installerbuilder/libinstaller ../../installerbuilder/common

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
TARGET = downloadspeed

QT -= gui
QT += core network
LIBS = -L$$OUT_PWD/../../installerbuilder/lib -linstaller $$LIBS

SOURCES += main.cpp
