#include "OpenCVUtility.hpp"
#include <QtWidgets/qapplication.h>
#include <QtGui/qimage.h>
#include <QtCore/qtimer.h>
#include <cstdlib>
#include <ctime>

OpenCVUtility::OpenCVUtility(QObject * p):QObject(p) {}

OpenCVUtility::~OpenCVUtility() {}

void OpenCVUtility::construct() {
}

namespace {
static inline void __construct() {
    {   /*强制加载图片插件,加强运行期体验*/
        QImage * image_=new QImage(":/i_m_a_g_e_s_/images/000000.png");
        auto width_=image_->width(); (void)width_;
        auto height_=image_->height(); (void)height_;
        delete image_;
    }
    {
        /*设置随机种子*/
        std::srand(int(std::time(nullptr)));
    }
    OpenCVUtility::construct();
}
}

/*在QApplication构造时运行*/
Q_COREAPP_STARTUP_FUNCTION(__construct)



