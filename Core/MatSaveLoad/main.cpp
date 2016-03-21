#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <array>

static inline void run(MainWindow * window ) {
    const QByteArray fileName = QDir::cleanPath( qApp->applicationDirPath() ).toLocal8Bit()+"/core_mat_saveload_test.xml";
    QImage image0("images:000000");

    auto imageMat=qImage2CVmat(image0);
    {
        /*提高亮度*/
        imageMat.first*=1.3;
        /*保存图片*/
        {
            cv::FileStorage file(
                cv::String(fileName.constData(),fileName.size()),
                cv::FileStorage::WRITE
                );
            file<<"images_000000"<<imageMat.first;
        }
        /*重新载入图片*/
        {
            cv::FileStorage file(
                cv::String(fileName.constData(),fileName.size()),
                cv::FileStorage::READ
                );
            file["images_000000"]>>imageMat.first;
        }
    }

    window->insertImage(image0)->setWindowTitle(u8R"(原始图片)"_qs);
    window->insertImage( imageMat.second )\
        ->setWindowTitle(u8R"(读入图片)"_qs);
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



