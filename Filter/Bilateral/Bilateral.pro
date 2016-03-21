CONFIG += c++14
CONFIG += console

QT += core
QT += gui
QT += widgets
QT += charts


TARGET = FilterBilateral
TEMPLATE = app


SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp

HEADERS += $$PWD/MainWindow.hpp

DEFINES += BUILD_PATH_=\\\"$$PWD\\\"

include( $$PWD/../../OpenCVUtility/OpenCVUtility.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lOpenCVUtilityd
}else{
LIBS += -L$$OUTPWD -lOpenCVUtility
}

DISTFILES += $$PWD/doc/doc.docx




