#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <QtCore/qtimer.h>
#include <iostream>
#include <fstream>

inline QString searchImageFileName(const QString & fileName_) {
    static const QString file_name_more_[]{ 
        "",".png",".jpg",".jpeg",".bmp",".gif" 
    };
    for (const QString & i:file_name_more_) {
        QString fileName=fileName_+i;
        {
            QFileInfo info(fileName);
            if (info.exists()) { return QDir::cleanPath(info.absoluteFilePath()); }
        }
        int index_ = fileName.indexOf(":");
        if (index_<0) { continue; }
        QString search_=fileName.left(index_);
        fileName=fileName.mid(1+index_);
        const QStringList & spath_ = QDir::searchPaths(search_);
        for (const QString & sp_:spath_) {
            QDir dir_(sp_);
            QFileInfo info_( dir_.filePath(fileName) );
            if (info_.exists()) {
                return QDir::cleanPath(info_.absoluteFilePath());
            }
        }
    }
    return "";
}

static inline void run(MainWindow * window) {
       
    QImage image0("images:000000");
    window->insertImage(image0);
    {
        QImage imageBlur=image0;
        cv::Mat ans_=OpenCVUtility::read(std::move(imageBlur));
        cv::blur(ans_,ans_,{ 3,3 });
        window->insertImage(OpenCVUtility::getInnerQImage(ans_));
    }
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



