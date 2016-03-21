#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <array>
#include <cmath>

inline static int maxLength(double dx,double dy) {
    return qRound( std::sqrt(dx*dx+dy*dy) );
}

static inline void run(MainWindow * window ) {

    QImage image0("images:000000");

    const float width_image_=image0.width();
    const float height_image_=image0.height();

    const std::vector< cv::Point2f > from_{ 
        {0,0},
        {0,height_image_},
        {width_image_,height_image_}, 
        {width_image_,0} 
    };

    const std::vector< cv::Point2f > to_{ 
        {0,0},
        {0,height_image_},
        {width_image_,height_image_/4*3}, 
        {width_image_,height_image_/4} 
    };

    cv::Mat atmax_ = cv::getPerspectiveTransform(from_,to_);

    auto cvImage0=qImage2CVmat(image0);
   
    auto ansSize=cv::Size(image0.width(),image0.height());
    cv::Mat ans(ansSize,cvImage0.first.type());

    cv::warpPerspective(cvImage0.first,ans ,atmax_,ansSize);

    window->insertImage( cvMat2QImage(ans).first.copy() )
        ->setWindowTitle(QObject::trUtf8(u8"变换后图像"));
    window->insertImage(image0)
        ->setWindowTitle(QObject::trUtf8(u8"原始图像"));
    
}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
    std::srand((int)std::time(0));
    QApplication app(argc, argv);

    {
        QDir::addSearchPath("images",app.applicationDirPath()+"/Images");
        QDir::addSearchPath("images",BUILD_PATH_);
        QDir::addSearchPath("images",BUILD_PATH_"/../../Images");
    }

    MainWindow * window =  new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    run(window);
    window->show();
    std::cout.flush();

    return app.exec();
}



