#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <array>

static inline void run(MainWindow * window ) {

    QImage image0("images:000000");
    auto imageMat=qImage2CVmat(image0);
    std::vector<cv::Mat> rgbMat;
    cv::split(imageMat.first,rgbMat);
    rgbMat[0]*=1.5;
    cv::merge(rgbMat,imageMat.first);
    window->insertImage(imageMat.second)->setWindowTitle(u8R"(增强红色通道)"_qs);
    window->insertImage(image0)->setWindowTitle(u8R"(原始图像)"_qs);
}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
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



