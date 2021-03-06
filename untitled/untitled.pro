#-------------------------------------------------
#  Copyright 2014 ESRI
#
#  All rights reserved under the copyright laws of the United States
#  and applicable international laws, treaties, and conventions.
#
#  You may freely redistribute and use this sample code, with or
#  without modification, provided you include the original copyright
#  notice and use restrictions.
#
#  See the Sample code usage restrictions document for further information.
#-------------------------------------------------

TARGET = untitled 
TEMPLATE = app

QT += core gui opengl xml network

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

# After installing the Runtime SDK for Qt you'll need to copy the
# esri_runtime_qt_10_2_3.prf file from your qt10.2.3/sdk/ideintegration folder
# to your Qt SDK's mkspecs/features folder in order for Qt Creator to locate 
# the ArcGIS Runtime SDK for Qt header files and libraries.
#
CONFIG += c++11 esri_runtime_qt_10_2_3 

win32:CONFIG += \
  embed_manifest_exe


SOURCES += \
	main.cpp \
        untitled.cpp 

HEADERS += \
	untitled.h

