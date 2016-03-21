#include "MainWindow.hpp"
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
    QImage imageAns(image0.size(),QImage::Format_RGB888);

    auto mat=qImage2CVmat(image0);
    auto mat1=qImage2CVmat(image0.copy());
    auto matAns=qImage2CVmat(imageAns);

    cv::bilateralFilter(mat.first,matAns.first,3,.1,.2);
    cv::blur(mat1.first,mat1.first,{3,3});
    
    window->insertImage(image0)
        ->setWindowTitle(QObject::trUtf8(u8"原始图像"));

    window->insertImage( matAns.second )
        ->setWindowTitle(QObject::trUtf8(u8"变换后图像"));

    window->insertImage( mat1.second )
        ->setWindowTitle(QObject::trUtf8(u8"blur"));
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



