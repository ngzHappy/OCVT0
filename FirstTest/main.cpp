#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <QtCore/qtimer.h>
#include <iostream>
#include <fstream>

static inline void run(MainWindow * window) {

    window->insertImage(QImage("images:000000"))->setWindowTitle("0");
    window->insertImage(QImage("images:000001"))->setWindowTitle("1");
    auto * item_=window->insertHist({ 1,2,3 });
    item_->setWindowTitle("2");

    std::pair<cv::Mat,QImage> matImage=qImage2CVmat(QImage("images:000002"));
    cv::Mat ans0,ans1;
    cv::decolor(matImage.first,ans0,ans1);
    window->insertImage(cvMat2QImage(ans0).first.copy())
        ->setWindowTitle(u8"灰度图"_qs);
    window->insertImage(cvMat2QImage(ans1).first.copy())
        ->setWindowTitle(u8"增强彩色图"_qs);
    window->insertImage(QImage("images:000002"))
        ->setWindowTitle(u8"原图"_qs);

    const std::string fileName=
        (qApp->applicationDirPath()+"/gray.txt").toLocal8Bit().toStdString();
    std::cout<<"fileName: "<<fileName<<std::endl;
    std::ofstream ofs(fileName);
    ofs<<ans0<<std::endl;

}

int main(int argc,char *argv[]) {
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
    QApplication app(argc,argv);

    {
        QDir::addSearchPath("images",app.applicationDirPath()+"/Images");
        QDir::addSearchPath("images",BUILD_PATH_);
        QDir::addSearchPath("images",QDir::cleanPath(BUILD_PATH_"/../Images"));
    }

    MainWindow * window=new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    run(window);
    window->show();
    std::cout.flush();

    return app.exec();
}



