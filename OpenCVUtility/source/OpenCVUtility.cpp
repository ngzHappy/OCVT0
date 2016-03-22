#include "OpenCVUtility.hpp"
#include <QtWidgets/qapplication.h>
#include <QtGui/qimage.h>
#include <QtCore/qtimer.h>
#include <private/qimage_p.h>
#include <cstdlib>
#include <ctime>
#include <cassert>

OpenCVUtility::OpenCVUtility(QObject * p):QObject(p) {}

OpenCVUtility::~OpenCVUtility() {}

void OpenCVUtility::construct() {
}

namespace {

void deleteAny( QVariant * data_ ) {
    delete data_;
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
        if (data0) { u->flags|=UMatData::USER_ALLOCATED; }

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
            assert( u->handle == &deleteAny );
            deleteAny(reinterpret_cast<QVariant *>(u->userdata));
#if defined(_DEBUG)
            qDebug()<<"destory qimage "<<__func__;
#endif
        }

        delete u;
    }
};

}

namespace {
static cv::MatAllocator * stdMalloc=nullptr;
static inline void __construct() {
    {   /*强制加载图片插件,加强运行期体验*/
        QImage * image_=new QImage(":/i_m_a_g_e_s_/images/000000.png");
        auto width_=image_->width(); (void)width_;
        auto height_=image_->height(); (void)height_;
        assert( width_>0 );
        assert( height_>0 );
        delete image_;
    }
    {
        /*设置随机种子*/
        std::srand(int(std::time(nullptr)));
    }
    {
        /*设置OpenCV内存分配策略*/
        if (stdMalloc==nullptr) {
            stdMalloc=new StdMatAllocator;
            cv::Mat::setDefaultAllocator(stdMalloc);
            qAddPostRoutine([]() {
                cv::Mat::setDefaultAllocator(nullptr);
                delete stdMalloc;
                stdMalloc=0;
            });
        }
    }
    OpenCVUtility::construct();
}
}

OpenCVUtility::Handle OpenCVUtility::getHandle() {
    return &deleteAny;
}

cv::Mat OpenCVUtility::read(const QString & string_) {
    QImage image_(string_);
    return read( std::move(image_) );
}

cv::Mat OpenCVUtility::read(QImage && image_) {
    if (image_.width()<=0) { return cv::Mat(); }
    if (image_.height()<=0) { return cv::Mat(); }
    image_.detach();

    QImage::Format format_ = image_.format();
    switch (format_) {
        case QImage::Format_Invalid:break;
        case QImage::Format_Mono:break;
        case QImage::Format_MonoLSB:break;
        case QImage::Format_Indexed8:break;
        case QImage::Format_RGB32: {
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_ARGB32: {
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_ARGB32_Premultiplied:{
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_RGB16:{
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_ARGB8565_Premultiplied:{
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_RGB666:{
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_ARGB6666_Premultiplied: {
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_RGB555: {
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_ARGB8555_Premultiplied: {
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_RGB888: break;
        case QImage::Format_RGB444: {
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_ARGB4444_Premultiplied: {
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_RGBX8888: {
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_RGBA8888: {}break;
        case QImage::Format_RGBA8888_Premultiplied: {
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_BGR30: {
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_A2BGR30_Premultiplied: {
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_RGB30: {
            image_=image_.convertToFormat(QImage::Format_RGB888);
        }break;
        case QImage::Format_A2RGB30_Premultiplied: {
            image_=image_.convertToFormat(QImage::Format_RGBA8888);
        }break;
        case QImage::Format_Alpha8:break;
        case QImage::Format_Grayscale8:break;
        case QImage::NImageFormats:break;
        default:break;
    }
    format_ = image_.format();

    if ( format_ == QImage::Format_RGB888 ) {
        cv::Mat xmat_(
            image_.height(),
            image_.width(),
            CV_8UC3,
            image_.bits(),
            image_.bytesPerLine()
            );
        assert( xmat_.u == nullptr );
        xmat_.u=cv::Mat::getDefaultAllocator()
            ->allocate(0,nullptr,0,image_.bits(),nullptr,0,cv::USAGE_DEFAULT);
        assert( xmat_.u->userdata == nullptr );
        assert( xmat_.u->handle == nullptr );
        xmat_.u->handle = reinterpret_cast<void *>( OpenCVUtility::getHandle() );
        xmat_.u->userdata=new QVariant(QImage(std::move(image_)));
        xmat_.u->refcount=1;
        return std::move(xmat_);
    }
    else if ( format_ == QImage::Format_RGBA8888 ) {
        cv::Mat xmat_(
            image_.height(),
            image_.width(),
            CV_8UC4,
            image_.bits(),
            image_.bytesPerLine()
            );
        assert( xmat_.u == nullptr );
        xmat_.u=cv::Mat::getDefaultAllocator()
            ->allocate(0,nullptr,0,image_.bits(),nullptr,0,cv::USAGE_DEFAULT);
        assert( xmat_.u->userdata == nullptr );
        assert( xmat_.u->handle == nullptr );
        xmat_.u->handle= reinterpret_cast<void *>(OpenCVUtility::getHandle());
        xmat_.u->userdata=new QVariant(QImage(std::move(image_)));
        xmat_.u->refcount=1;
        return std::move(xmat_);
    }
    else {
        if (format_==QImage::Format_Grayscale8) {
            cv::Mat xmat_(
                image_.height(),
                image_.width(),
                CV_8UC1,
                image_.bits(),
                image_.bytesPerLine()
                );
            assert( xmat_.u == nullptr );
            xmat_.u=cv::Mat::getDefaultAllocator()
                ->allocate(0,nullptr,0,image_.bits(),nullptr,0,cv::USAGE_DEFAULT);
            assert( xmat_.u->userdata == nullptr );
            assert( xmat_.u->handle == nullptr );
            xmat_.u->handle= reinterpret_cast<void *>(OpenCVUtility::getHandle());
            xmat_.u->userdata=new QVariant(QImage(std::move(image_)));
            xmat_.u->refcount=1;
            return std::move(xmat_);
        }
        else {
            return cv::Mat();
        }
    }

}

namespace  {
void handle_qimage_(void * v){
    delete reinterpret_cast<cv::Mat *>( v );
}
}

OpenCVUtility::HandleQImage OpenCVUtility::getHandleQImage(){
    return &handle_qimage_;
}

cv::Mat OpenCVUtility::getInnerOpenCVMat(const QImage & image_){
    QImage::DataPtr data_ = const_cast<QImage &>(image_).data_ptr();
    if(data_){
        if( data_->cleanupInfo ){
            if( data_->cleanupFunction == getHandleQImage() ){
                return *( reinterpret_cast<cv::Mat *>( data_->cleanupInfo ) );
            }
        }
    }
    return cv::Mat();
}

QImage OpenCVUtility::getInnerQImage(const cv::Mat & v) {
    if (v.u) {
        if (v.u->userdata) {
            assert( v.u->handle == OpenCVUtility::getHandle() );
            return reinterpret_cast<QVariant *>( v.u->userdata )->value<QImage>();
        }
    }
    return QImage();
}

/*在QApplication构造时运行*/
Q_COREAPP_STARTUP_FUNCTION(__construct)



