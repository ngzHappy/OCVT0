CONFIG += c++14
CONFIG += console

QT += core
QT += gui
QT += widgets
QT += charts


TARGET = GeometricImageTransformationsRemap
TEMPLATE = app


SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp

HEADERS += $$PWD/MainWindow.hpp

DEFINES += BUILD_PATH_=\\\"$$clean_path($$PWD)\\\"

include( $$PWD/../../OpenCVUtility/OpenCVUtility.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lOpenCVUtilityd
}else{
LIBS += -L$$OUTPWD -lOpenCVUtility
}




