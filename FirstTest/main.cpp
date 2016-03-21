#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <QtCore/qtimer.h>
#include <iostream>

static inline void run(MainWindow * window) {
    
    window->insertImage(QImage("images:000000"))->setWindowTitle("0");
    window->insertImage(QImage("images:000001"))->setWindowTitle("1");
    auto * item_=window->insertHist({ 1,2,3 });
    item_->setWindowTitle("2");

}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
    QApplication app(argc, argv);

    {
        QDir::addSearchPath("images",app.applicationDirPath()+"/Images");
        QDir::addSearchPath("images",BUILD_PATH_);
        QDir::addSearchPath("images",BUILD_PATH_"/../Images");
    }

    MainWindow * window =  new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    run(window);
    window->show();
    std::cout.flush();

    return app.exec();
}



