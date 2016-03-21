#include "OpenCVMatQImage.hpp"
#include <QtGui/qimage.h>
#include <memory>

std::pair<QImage,cv::Mat> cvMat2QImage(cv::Mat mat_) {
    std::pair<QImage,cv::Mat> ans_;

    if ((mat_.rows>0)&&
        (mat_.cols>0)) {

        switch (mat_.type()) {
            case CV_8UC3: {
                ans_.first=QImage(
                    mat_.data,
                    mat_.cols,
                    mat_.rows,
                    mat_.step,
                    QImage::Format::Format_RGB888);
            }break;
            case CV_8UC4: {
                ans_.first=QImage(
                     mat_.data,
                     mat_.cols,
                     mat_.rows,
                     mat_.step,
                     QImage::Format::Format_RGBA8888);
            }break;
            case CV_8UC1: {
                ans_.first=QImage(
                    mat_.data,
                    mat_.cols,
                    mat_.rows,
                    mat_.step,
                    QImage::Format::Format_Grayscale8);
            }break;
        }

    }
    ans_.second=std::move(mat_);
    return std::move(ans_);
}

std::pair<cv::Mat,QImage> qImage2CVmat(QImage image_) {
    std::pair<cv::Mat,QImage> ans_;
    if ((image_.height()>0)
        &&(image_.width()>0)) {
        image_=image_.convertToFormat(QImage::Format::Format_RGB888);
        cv::Mat ans(
            image_.height(),image_.width(),
            CV_8UC3,const_cast<uchar *>(image_.bits()),image_.bytesPerLine()
            );
        ans_.first=std::move(ans);
    }
    ans_.second=std::move(image_);
    return std::move(ans_);
}




