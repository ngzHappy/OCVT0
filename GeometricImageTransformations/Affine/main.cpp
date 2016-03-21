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

    auto len_ =maxLength(width_image_,height_image_ );

    const float diff_width_image_=0.0f;
    const float diff_height_image_=len_/2;

    std::vector< cv::Point2f > from_{ {0,4},{4,0},{0,0} };
    std::vector< cv::Point2f > to_{
        {2+diff_width_image_,diff_height_image_+2},
        {2+diff_width_image_,diff_height_image_-2},
        {diff_width_image_,diff_height_image_}
    };

    cv::Mat atmax_ = cv::getAffineTransform(from_,to_);

    auto cvImage0=qImage2CVmat(image0);
    cv::Mat ans( len_,len_,atmax_.type() );
    cv::warpAffine(cvImage0.first,ans,atmax_,{len_,len_});

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
        QDir::addSearchPath("images",QDir::cleanPath(BUILD_PATH_"/../../Images"));
    }

    MainWindow * window =  new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    run(window);
    window->show();
    std::cout.flush();

    return app.exec();
}



