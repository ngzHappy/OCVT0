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
       
    {
        QImage image__("images:000000");
        cv::Mat xmat_(
            image__.height(),
            image__.width(),
            CV_8UC3,
            image__.bits(),
            image__.bytesPerLine()
            );

        xmat_.u=cv::Mat::getDefaultAllocator()
            ->allocate(0,nullptr,0,image__.bits(),nullptr,0,cv::USAGE_DEFAULT);
        xmat_.u->userdata=new QVariant(QImage(std::move(image__)));
        xmat_.u->refcount=1;
    }

   /* cv::Mat ymat=xmat_;
    cv::Mat zmat(1,2,CV_8UC3);*/

    cv::DataType<float>::type;
    QByteArray fileName_ = searchImageFileName("images:000000").toLocal8Bit();

    cv::Mat mat_ = cv::imread(fileName_.constData());
    cv::cvtColor( mat_,mat_,CV_BGR2RGB );

    cv::Mat::getStdAllocator();
    cv::Mat::getDefaultAllocator();

    QImage image(
        mat_.data,
        mat_.cols,
        mat_.rows,
        mat_.step,
        QImage::Format_RGB888,
        [](void * d) {cv::Mat * mat__=reinterpret_cast<cv::Mat *>(d);delete mat__;},
        new cv::Mat(mat_)
        );
    window->insertImage(image);
    mat_.release();
}

class StdMatAllocator : public cv::MatAllocator
{
public:
    cv::UMatData* allocate(
        int dims, 
        const int* sizes, 
        int type,
        void* data0, 
        size_t* step, 
        int /*flags*/,
        cv::UMatUsageFlags /*usageFlags*/) const{

        using namespace cv;
        size_t total = CV_ELEM_SIZE(type);
        for( int i = dims-1; i >= 0; i-- )
        {
            if( step ){
                if( data0 && step[i] != CV_AUTOSTEP ){
                    CV_Assert(total <= step[i]);
                    total = step[i];
                }
                else {
                    step[i]=total; 
                }
            }
            total *= sizes[i];
        }

        uchar* data = data0 ? (uchar*)data0 : (uchar*)fastMalloc(total);
        UMatData* u = new UMatData(this);
        u->data = u->origdata = data;
        u->size = total;
        if(data0)
            u->flags |= UMatData::USER_ALLOCATED;

        return u;
    }

    bool allocate(
        cv::UMatData* u, 
        int /*accessFlags*/, 
        cv::UMatUsageFlags /*usageFlags*/) const{
        if(!u) return false;
        return true;
    }

    void deallocate(cv::UMatData* u) const{
        using namespace cv;
        if(!u) return;

        CV_Assert(u->urefcount == 0);
        CV_Assert(u->refcount == 0);

        if( !(u->flags & UMatData::USER_ALLOCATED) ){
            fastFree(u->origdata);
            u->origdata = 0;
        }

        if (u->userdata) {
            delete reinterpret_cast<QVariant *>(u->userdata);
        }

        delete u;
    }
};

int main(int argc,char *argv[]) {
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
    QApplication app(argc,argv);

    auto * opencvAlloc=new StdMatAllocator;
    cv::Mat::setDefaultAllocator(opencvAlloc);

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
    delete opencvAlloc;
   // system("pause");
}



