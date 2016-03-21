#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <array>

namespace __private{
template<
    typename _T_,
    typename _Function_,
    typename ... Args
>
static inline void value(
    _T_ * const startPointer_,
    const std::size_t width_,
    const std::size_t height_,
    std::size_t perLineSize_ ,
    const _Function_ & fun_/*function(_T_ * , ... )*/,
    Args && ... args_
    ) {
    if (perLineSize_<width_) { perLineSize_=width_; }
    _T_ * linePointer_=startPointer_;
    std::size_t y_=0;
    std::size_t x_=0;
    for (;y_<height_;++y_) {
        _T_ * lineStart_=linePointer_;
        const _T_ * const lineEnd_=linePointer_+width_;
        for (x_=0;lineStart_!=lineEnd_;++lineStart_,++x_) {
            fun_(lineStart_,x_,y_,std::forward<Args>(args_)...);
        }
        linePointer_+=perLineSize_;
    }
}
}

static inline void run(MainWindow * window ) {

    QImage image0("images:000000");
    window->insertImage(image0)->setWindowTitle(QObject::trUtf8(u8"原始图像"));

    {
        const auto image_width_=image0.width();
        const auto image_height_=image0.height();

        /*flip x,y*/
        cv::Mat flipX(image_height_,image_width_,CV_32FC1);
        cv::Mat flipY(image_height_,image_width_,CV_32FC1);

        __private::value(
            flipX.ptr<float>(),
            image_width_,image_height_,
            (flipX.step.buf[0])/(flipX.step.buf[1]),
            [](
            float * data_,
            std::size_t x_,std::size_t,
            std::int32_t width__) {*data_=width__-x_; },
            image_width_-1
            );

        __private::value(
            flipY.ptr<float>(),
            image_width_,image_height_,
            (flipY.step.buf[0])/(flipY.step.buf[1]),
            [](
            float * data_,
            std::size_t ,std::size_t y_,
            std::int32_t height__) {*data_=height__-y_; },
            image_height_-1
            );

        auto cvImage_ = qImage2CVmat(image0);
        cv::Mat ans;
        cv::remap(cvImage_.first,ans,flipX,flipY,cv::InterpolationFlags::INTER_LINEAR);
        
        ans.copyTo(cvImage_.first);
        window->insertImage( cvImage_.second )
            ->setWindowTitle(QObject::trUtf8(u8"变换后图像"));
    }

    {
        const auto image_width_=image0.width();
        const auto image_height_=image0.height();

        /*flip x,y*/
        cv::Mat flipX(image_height_,image_width_,CV_32FC1);
        cv::Mat flipY(image_height_,image_width_,CV_32FC1);

        enum {RandomSize=8};
        std::array<std::int32_t,RandomSize> randomX,randomY;
        for (int i=0; i<RandomSize; ++i) { 
            randomX[i]=i;randomY[i]=i;
        }

        std::shuffle(randomX.begin(),randomX.end(),
            std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
        std::shuffle(randomY.begin(),randomY.end(),
            std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

        __private::value(
            flipX.ptr<float>(),
            image_width_,image_height_,
            (flipX.step.buf[0])/(flipX.step.buf[1]),
            [&randomX](
            float * data_,
            std::size_t x_,std::size_t,
            std::size_t max_) {
            *data_=std::min<float>((x_/RandomSize*RandomSize)+randomX[(x_%RandomSize)],max_);
        },
            image_width_-1
            );

        __private::value(
            flipY.ptr<float>(),
            image_width_,image_height_,
            (flipY.step.buf[0])/(flipY.step.buf[1]),
            [&randomY](
            float * data_,
            std::size_t ,std::size_t y_,
            std::size_t max_) {
            *data_=std::min<float>((y_/RandomSize*RandomSize)+randomY[(y_%RandomSize)],max_);
        },
            image_height_-1
            );

        auto cvImage_ = qImage2CVmat(image0);
        cv::Mat ans;
        cv::remap(cvImage_.first,ans,flipX,flipY,cv::InterpolationFlags::INTER_LINEAR);

        ans.copyTo(cvImage_.first);
        window->insertImage( cvImage_.second )
            ->setWindowTitle(QObject::trUtf8(u8"随机晶格化"));

    }

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



