﻿#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <array>

static inline void run(MainWindow * window ) {

    QImage image0("images:000003");

    auto mat=qImage2CVmat(image0);

    cv::blur(mat.first,mat.first,{3,3});

    window->insertImage(image0)
        ->setWindowTitle(QObject::trUtf8(u8"原始图像"));

    window->insertImage( mat.second )
        ->setWindowTitle(QObject::trUtf8(u8"变换后图像"));

}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
    std::srand((int)std::time(0));
    QApplication app(argc, argv);

    {
        QDir::addSearchPath("images",app.applicationDirPath()+"/Images");
        QDir::addSearchPath("images",BUILD_PATH_);
        QDir::addSearchPath("images",QDir::cleanPath(BUILD_PATH_"/../../Images"));
    }

    MainWindow * window =  new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    run(window);
    window->show();
    std::cout.flush();

    return app.exec();
}



