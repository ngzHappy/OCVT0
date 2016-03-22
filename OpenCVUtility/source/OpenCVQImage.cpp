#include "../OpenCVQImage.hpp"
#include <string>

namespace {
namespace __private {
template<typename _T_>
void __destory(_T_ * d) { d->~_T_(); }
}
}

void OpenCVQImage::_construct() {
    _setType(Type::Nil);
}
void OpenCVQImage::_construct(const QImage & v) {
    _setType(Type::QtImage);
    new(&data_.image_.value) QImage(v);
    new(&data_.image_.mat) Mat();
}
void OpenCVQImage::_construct(QImage && v) {
    _setType(Type::QtImage);
    new(&data_.image_.value) QImage(std::move(v));
    new(&data_.image_.mat) Mat();
}
void OpenCVQImage::_construct(const cv::Mat & v) {
    _setType(Type::OpenCVMat);
    new(&data_.mat_.value) cv::Mat(v);
    new(&data_.mat_.image) QImage();
}
void OpenCVQImage::_construct(cv::Mat && v) {
    _setType(Type::OpenCVMat);
    new(&data_.mat_.value) cv::Mat(std::move(v));
    new(&data_.mat_.image) QImage();
}
void OpenCVQImage::_copy() {}
void OpenCVQImage::_copy(const QImage & v) {
    data_.image_.value=v;
}
void OpenCVQImage::_copy(QImage && v) {
    data_.image_.value=std::move(v);
}
void OpenCVQImage::_copy(const cv::Mat & v) {
    data_.mat_.value=v;
}
void OpenCVQImage::_copy(cv::Mat && v) {
    data_.mat_.value=std::move(v);
}

void OpenCVQImage::_destruct() {
    switch (getType()) {
        case Type::Nil:break;
        case Type::QtImage: {
            _setType(Type::Nil);
            __private::__destory(&data_.image_.value);
            __private::__destory(&data_.image_.mat);
        } break;
        case Type::OpenCVMat: {
            _setType(Type::Nil);
            __private::__destory(&data_.mat_.value);
            __private::__destory(&data_.mat_.image);
        }break;
        default:_setType(Type::Nil);; break;
    }
}

OpenCVQImage::OpenCVQImage(const OpenCVQImage & v) {
    switch (v.getType()) {
        case Type::Nil:_construct(); break;
        case Type::QtImage:_construct(v.data_.image_.value); break;
        case Type::OpenCVMat:_construct(v.data_.mat_.value); break;
        default:_construct(); break;
    }
}

OpenCVQImage::OpenCVQImage(OpenCVQImage && v) {
    switch (v.getType()) {
        case Type::Nil:_construct(); break;
        case Type::QtImage:_construct(std::move(v.data_.image_.value)); break;
        case Type::OpenCVMat:_construct(std::move(v.data_.mat_.value)); break;
        default:_construct(); break;
    }
}

OpenCVQImage & OpenCVQImage::setValue(const QImage & v) {
    if (getType()==Type::QtImage) {
        _copy(v);
        return *this;
    }
    _destruct();
    _construct(v);
    return *this;
}

OpenCVQImage & OpenCVQImage::setValue(QImage && v) {
    if (getType()==Type::QtImage) {
        _copy(std::move(v));
        return *this;
    }
    _destruct();
    _construct(std::move(v));
    return *this;
}

OpenCVQImage & OpenCVQImage::setValue(const cv::Mat & v) {
    if (getType()==Type::OpenCVMat) {
        _copy(v);
        return *this;
    }
    _destruct();
    _construct(v);
    return *this;
}

OpenCVQImage & OpenCVQImage::setValue(cv::Mat && v) {
    if (getType()==Type::OpenCVMat) {
        _copy(std::move(v));
        return *this;
    }
    _destruct();
    _construct(std::move(v));
    return *this;
}

OpenCVQImage & OpenCVQImage::setValue(const OpenCVQImage & v) {
    if (this==&v) { return *this; }
    switch (v.getType()) {
        case Type::Nil:return setValue();
        case Type::QtImage:return setValue(v.data_.image_.value);
        case Type::OpenCVMat:; return setValue(v.data_.mat_.value);
    }
    _copy();
    return *this;
}

OpenCVQImage & OpenCVQImage::setValue(OpenCVQImage && v) {
    if (this==&v) { return *this; }
    switch (v.getType()) {
        case Type::Nil:return setValue();
        case Type::QtImage:return setValue(std::move(v.data_.image_.value));
        case Type::OpenCVMat:; return setValue(std::move(v.data_.mat_.value));
    }
    _copy();
    return *this;
}

namespace {
namespace __private {
static QImage * image=nullptr;
static cv::Mat * mat=nullptr;
}
}

OpenCVQImage::operator const QImage&() const noexcept(false) {
    if (getType()==Type::QtImage) { return data_.image_.value; }
    if (getType()==Type::OpenCVMat) {
        return _to_qimage();
    }
    if (getType()==Type::Nil) {
        const_cast<OpenCVQImage * const>(this)->_construct(QImage());
        return data_.image_.value;
    }
    if (__private::image==nullptr) {
        __private::image=new QImage;
        qAddPostRoutine([]() {delete __private::image; __private::image=nullptr; });
    }
    return *__private::image;
}

OpenCVQImage::operator const OpenCVQImage::Mat&() const noexcept(false) {
    if (getType()==Type::OpenCVMat) { return data_.mat_.value; }
    if (getType()==Type::QtImage) {
        return _to_mat();
    }
    if (getType()==Type::Nil) {
        const_cast<OpenCVQImage * const>(this)->_construct(Mat());
        return data_.mat_.value;
    }
    if (__private::mat==nullptr) {
        __private::mat=new cv::Mat;
        qAddPostRoutine([]() {delete __private::mat; __private::mat=nullptr; });
    }
    return *__private::mat;
}

OpenCVQImage::operator QImage&()noexcept(false) {
    if (getType()==Type::QtImage) { return data_.image_.value; }
    if (getType()==Type::OpenCVMat) {
        return __to_qimage();
    }
    if (getType()==Type::Nil) {
        _construct(QImage());
        return data_.image_.value;
    }
    if (__private::image==nullptr) {
        __private::image=new QImage;
        qAddPostRoutine([]() {delete __private::image; __private::image=nullptr; });
    }
    return *__private::image;
}

OpenCVQImage::operator OpenCVQImage::Mat&()noexcept(false) {
    if (getType()==Type::OpenCVMat) { return data_.mat_.value; }
    if (getType()==Type::QtImage) {
        return __to_mat();
        throw (std::string(__func__));
    }
    if (getType()==Type::Nil) {
        _construct(Mat());
        return data_.mat_.value;
    }
    if (__private::mat==nullptr) {
        __private::mat=new cv::Mat;
        qAddPostRoutine([]() {delete __private::mat; __private::mat=nullptr; });
    }
    return *__private::mat;
}

const QImage & OpenCVQImage::_to_qimage() const {
    return const_cast<OpenCVQImage * const>(this)->__to_qimage();
}

const OpenCVQImage::Mat & OpenCVQImage::_to_mat() const {
    return const_cast<OpenCVQImage * const>(this)->__to_mat();
}

QImage & OpenCVQImage::__to_qimage() {
    auto & data__=data_.mat_;
    if (
        (data__.image.constBits()!=data__.value.data)||
        (data__.image.width()!=data__.value.cols)||
        (data__.image.height()!=data__.value.rows)
       ) {
        //qDebug()<<"convert:::";
        switch (data__.value.type()) {
            case CV_8UC3: {
                data__.image=QImage(
                     data__.value.data,
                     data__.value.cols,
                     data__.value.rows,
                     data__.value.step,
                     QImage::Format::Format_RGB888);
            }break;
            case CV_8UC4: {
                data__.image=QImage(
                    data__.value.data,
                    data__.value.cols,
                    data__.value.rows,
                    data__.value.step,
                    QImage::Format::Format_RGBA8888);
            }break;
            case CV_8UC1: {
                data__.image=QImage(
                    data__.value.data,
                    data__.value.cols,
                    data__.value.rows,
                    data__.value.step,
                    QImage::Format::Format_Grayscale8);
            }break;
            default: throw (std::string(__func__)+" "+__FILE__+" type ????"); break;
        }
    }
    return data__.image;
}

OpenCVQImage::Mat & OpenCVQImage::__to_mat() {
    auto & data__=data_.image_;
    if (
        (data__.mat.data!=data__.value.constBits())||
        (data__.mat.cols!=data__.value.width())||
        (data__.mat.rows!=data__.value.height())
        ) {
        //qDebug()<<"convert::::";
        QImage::Format type_=data__.value.format();
        bool isOk_=false;
    label_translate_:
        switch (type_) {
            case QImage::Format_Invalid:break;
            case QImage::Format_Mono:break;
            case QImage::Format_MonoLSB:break;
            case QImage::Format_Indexed8:break;
            case QImage::Format_RGB32: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGB888);
                goto label_translate_;
            }break;
            case QImage::Format_ARGB32: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_ARGB32_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_RGB16: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGB888);
                goto label_translate_;
            }break;
            case QImage::Format_ARGB8565_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            } break;
            case QImage::Format_RGB666: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGB888);
                goto label_translate_;
            }break;
            case QImage::Format_ARGB6666_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_RGB555: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGB888);
                goto label_translate_;
            }break;
            case QImage::Format_ARGB8555_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_RGB888: {
                isOk_=true;
                data__.mat=Mat(
                    data__.value.height(),
                    data__.value.width(),
                    CV_8UC3,
                    const_cast<uchar *>(data__.value.bits()),
                    data__.value.bytesPerLine()
                    );
            }break;
            case QImage::Format_RGB444: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGB888);
                goto label_translate_;
            }break;
            case QImage::Format_ARGB4444_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_RGBX8888:break;
            case QImage::Format_RGBA8888: {
                isOk_=true;
                data__.mat=Mat(
                    data__.value.height(),
                    data__.value.width(),
                    CV_8UC4,
                    const_cast<uchar *>(data__.value.bits()),
                    data__.value.bytesPerLine()
                    );
            }break;
            case QImage::Format_RGBA8888_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_BGR30: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGB888);
                goto label_translate_;
            }break;
            case QImage::Format_A2BGR30_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_RGB30: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGB888);
                goto label_translate_;
            }break;
            case QImage::Format_A2RGB30_Premultiplied: {
                data__.value=data__.value.convertToFormat(QImage::Format_RGBA8888);
                goto label_translate_;
            }break;
            case QImage::Format_Alpha8: break;
            case QImage::Format_Grayscale8: {
                isOk_=true;
                data__.mat=Mat(
                    data__.value.height(),
                    data__.value.width(),
                    CV_8UC1,
                    const_cast<uchar *>(data__.value.bits()),
                    data__.value.bytesPerLine()
                    );
            }break;
            case QImage::NImageFormats:break;
            default:break;
        }
        if (isOk_==false) {
            throw (std::string(__func__)+" "+__FILE__+" type ????");
        }
    }
    return data__.mat;
}

QImage OpenCVQImage::tryCopyQImage()const {
    const QImage & image_=*this;
    if (getType()==Type::QtImage) { return image_; }
    return image_.copy();
}

OpenCVQImage::Mat OpenCVQImage::tryCopyMat()const {
    const Mat & mat_=*this;
    if (getType()==Type::OpenCVMat) { return mat_; }
    return mat_.clone();
}

