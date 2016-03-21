#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextcodec.h>
#include <iostream>
#include <array>

static inline void run(MainWindow * window) {
    /*初始化一个空矩阵*/
    cv::Mat mat_null{};
    /*初始化一个 3X3 float矩阵*/
    cv::Mat mat_3x3_float{ cv::Size(3,3),CV_32FC1 ,cv::Scalar{0.0f} };
    /*初始化一个 3X3 <float,float,float>矩阵*/
    cv::Mat mat_3x3_float3{ cv::Size(3,3),CV_32FC3 ,cv::Scalar{1/2.0f,1/4.0f,1/8.0f} };
    std::cout<<"mat_3x3_float3="<<std::endl<<mat_3x3_float3<<std::endl;
    /*使用at修改数据*/
    std::get<0>(mat_3x3_float3.at< std::array<float,3> >(0,0))=1;
    std::cout<<"mat_3x3_float3="<<std::endl<<mat_3x3_float3<<std::endl;
    /*使用迭代器修改数据*/
    {
        auto b=mat_3x3_float3.begin<std::array<float,3>>();
        auto e=mat_3x3_float3.end<std::array<float,3>>();
        int i=0;
        for (;b!=e;++b) {
            if (i>2) { i=0; }
            (*b)[i]=i; ++i;
        }
        std::cout<<"mat_3x3_float3="<<std::endl<<mat_3x3_float3<<std::endl;
    };
    /*使用指针修改数据*/
    {
        /*获得首地址*/
        auto b = mat_3x3_float3.ptr<std::array<float,3>>();
        auto item_perline = mat_3x3_float3.step.buf[0]/mat_3x3_float3.step.buf[1];
        auto r=0;
        for (;r< mat_3x3_float3.rows;++r) {
            /*当前行地址*/
            auto lb=b;
            /*下一行地址*/
            b+=item_perline;
            for (;lb!=b;++lb) {
                (*lb)[1]=r;
            }
        }
        std::cout<<"mat_3x3_float3="<<std::endl<<mat_3x3_float3<<std::endl;
    }
    /*初始化一个 256X1 float矩阵*/
    cv::Mat mat_256x1_float{ cv::Size(256,1),CV_32FC1 ,cv::Scalar{0} };
    mat_256x1_float.forEach<float>([  ]( float & value_, auto) {
        value_= (std::rand()&63);
    });
    window->insertHist(
        mat_256x1_float.begin<float>(),
        mat_256x1_float.end<float>()
        );
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



