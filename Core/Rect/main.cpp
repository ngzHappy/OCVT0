#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <array>

static inline void run(MainWindow *  ) {

    {
        /*理解rect的边界*/
        cv::Rect2f rect(0,0,100,100);
        cv::Point2f point(100,100),point1(1,1),point2(0,0);

        std::cout<<"rect:"<<rect
            <<"contains:"<<"point:"<<point
            <<":"<<std::boolalpha<<rect.contains(point)
            <<std::endl;

        std::cout<<"rect:"<<rect
            <<"contains:"<<"point:"<<point2
            <<":"<<std::boolalpha<<rect.contains(point2)
            <<std::endl;

        std::cout<<"rect:"<<rect
            <<"contains:"<<"point:"<<point1
            <<":"<<std::boolalpha<<rect.contains(point1)
            <<std::endl;
    }

    {
        /*rect的运算*/
        cv::Rect2f rect1(0,0,100,100),rect2(10,10,120,120);
        std::cout<< (rect1 & rect2) <<std::endl;
        std::cout<< (rect1 | rect2) <<std::endl;
    }

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



