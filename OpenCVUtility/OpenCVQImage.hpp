#ifndef _OCV_QIMAGE_HPP_0x00
#define _OCV_QIMAGE_HPP_0x00() 1

#include "OpenCVUtility.hpp"

class OPENCVUTILITYSHARED_EXPORT OpenCVQImage {
public:
    enum class Type : std::int32_t {
        Nil,QtImage,OpenCVMat
    };
    typedef cv::Mat Mat;
private:
    union Data_ {
    public:
        struct { Type type; }nil_;
        struct { Type type; QImage value; cv::Mat mat; }image_;
        struct { Type type; cv::Mat value; QImage image; }mat_;
        Data_() {}
        ~Data_() {}
    }data_;

    void _construct();
    void _construct(const QImage &);
    void _construct(QImage &&);
    void _construct(const cv::Mat &);
    void _construct(cv::Mat &&);
    void _copy();
    void _copy(const QImage &);
    void _copy(QImage &&);
    void _copy(const cv::Mat &);
    void _copy(cv::Mat &&);
    void _destruct();
    void _setType(const Type & v) { data_.nil_.type=v; }

    QImage & __to_qimage();
    Mat & __to_mat();
    const QImage & _to_qimage() const;
    const Mat & _to_mat() const;
public:
    OpenCVQImage() { _construct(); }
    OpenCVQImage(const QString & v) { _construct(QImage(v)); }
    OpenCVQImage(const QImage & v) { _construct(v); }
    OpenCVQImage(QImage && v) { _construct(std::move(v)); }
    OpenCVQImage(const cv::Mat & v) { _construct(v); }
    OpenCVQImage(cv::Mat && v) { _construct(std::move(v)); }
    OpenCVQImage(const OpenCVQImage &);
    OpenCVQImage(OpenCVQImage &&);

    Type getType()const { return data_.nil_.type; }
    ~OpenCVQImage() { _destruct(); }

    OpenCVQImage & setValue() { _destruct(); return *this; }
    OpenCVQImage & setValue(const QImage &);
    OpenCVQImage & setValue(QImage &&);
    OpenCVQImage & setValue(const cv::Mat &);
    OpenCVQImage & setValue(cv::Mat &&);
    OpenCVQImage & setValue(const OpenCVQImage &);
    OpenCVQImage & setValue(OpenCVQImage &&);

    OpenCVQImage & operator=(const QImage & v) { return setValue(v); }
    OpenCVQImage & operator=(QImage && v) { return setValue(std::move(v)); }
    OpenCVQImage & operator=(const cv::Mat & v) { return setValue(v); }
    OpenCVQImage & operator=(cv::Mat && v) { return setValue(std::move(v)); }
    OpenCVQImage & operator=(const OpenCVQImage & v) { return setValue(v); }
    OpenCVQImage & operator=(OpenCVQImage && v) { return setValue(std::move(v)); }

    /*throw std::string*/
    operator const QImage &()const noexcept(false);
    /*throw std::string*/
    operator const OpenCVQImage::Mat &()const noexcept(false);
    /*throw std::string*/
    operator QImage &() noexcept(false);
    /*throw std::string*/
    operator OpenCVQImage::Mat &() noexcept(false);

    explicit operator bool() const { return getType()!=Type::Nil; }

    QImage & toQImage() noexcept(false){ return (*this); }
    const QImage & toQImage() const noexcept(false){ return (*this); }
    Mat & toOpenCVMat() noexcept(false){ return (*this); }
    const Mat & toOpenCVMat() const noexcept(false){ return (*this); }

    QImage tryCopyQImage()const;
    Mat tryCopyMat()const;
};

#endif

