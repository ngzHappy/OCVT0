CONFIG += c++14

QT += core
QT += widgets
QT += gui
QT += charts

CONFIG(debug,debug|release){
TARGET = OpenCVUtilityd
}else{
TARGET = OpenCVUtility
}

TEMPLATE = lib

DEFINES += OPENCVUTILITY_LIBRARY

SOURCES += $$PWD/source/OpenCVUtility.cpp
SOURCES += $$PWD/source/OpenCVHistItem.cpp
SOURCES += $$PWD/source/OpenCVImageItem.cpp
SOURCES += $$PWD/source/OpenCVStyle.cpp
SOURCES += $$PWD/source/OpenCVWindow.cpp
SOURCES += $$PWD/source/OpenCVItem.cpp
SOURCES += $$PWD/source/OpenCVScene.cpp
SOURCES += $$PWD/source/OpenCVMatQImage.cpp

HEADERS += $$PWD/OpenCVUtility.hpp
HEADERS += $$PWD/OpenCVMatQImage.hpp
HEADERS += $$PWD/OpenCVHistItem.hpp
HEADERS += $$PWD/OpenCVImageItem.hpp
HEADERS += $$PWD/OpenCVStyle.hpp
HEADERS += $$PWD/OpenCVWindow.hpp
HEADERS += $$PWD/OpenCVScene.hpp
HEADERS += $$PWD/OpenCVItem.hpp
HEADERS += $$PWD/ReadOnly.hpp
HEADERS += $$PWD/opencvutility_global.hpp

include(OpenCVUtility.pri)
DESTDIR = $$OUTPWD

DISTFILES += $$PWD/../Images/000000.jpg
DISTFILES += $$PWD/../Images/000001.jpg
DISTFILES += $$PWD/../Images/000002.jpg
DISTFILES += $$PWD/../Images/000003.jpg
DISTFILES += $$PWD/../Images/000004.png
DISTFILES += $$PWD/../Images/000005.png
DISTFILES += $$PWD/../Images/000006.jpg
DISTFILES += $$PWD/../Images/000007.jpg
