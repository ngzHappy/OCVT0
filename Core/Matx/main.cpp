#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <array>

static inline void run(MainWindow *  ) {

    cv::Matx33f mat3x3(
        1,2,3,
        4,5,6,
        7,8,9);

    std::cout<< mat3x3(1,1) <<std::endl;

}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
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



