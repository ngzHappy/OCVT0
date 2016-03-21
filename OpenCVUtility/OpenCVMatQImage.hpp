#ifndef _OPENCV_MAT_QT_IMAGE_
#define _OPENCV_MAT_QT_IMAGE_() 1

#include <utility>
#include <opencv2/opencv.hpp>
#include <QtGui/qimage.h>
#include "opencvutility_global.hpp"

/*
仅支持:CV_8UC3,CV_8UC4,CV_8UC1
注意:输出QImage仅仅是输入数据指针的包装
核心函数: QImage(
                    mat_.data,
                    mat_.cols,
                    mat_.rows,
                    mat_.step,
                    QImage::Format::Format_RGB888 );
*/
std::pair<QImage,cv::Mat> OPENCVUTILITYSHARED_EXPORT cvMat2QImage(cv::Mat mat_);
/*
转换为RGB格式,设计用于计算
注意:输出cv::Mat仅仅是输入数据指针的包装
核心函数: cv::Mat ans (
            image_.height(),image_.width(),
            CV_8UC3, const_cast<uchar *>(image_.bits()),image_.bytesPerLine()
            );
*/
std::pair<cv::Mat,QImage> OPENCVUTILITYSHARED_EXPORT qImage2CVmat(QImage image_);


#endif

