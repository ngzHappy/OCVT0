﻿#ifndef OPENCVUTILITY_HPP
#define OPENCVUTILITY_HPP() 1

#include <opencv2/opencv.hpp>
#include "opencvutility_global.hpp"
#include <cstdlib>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <functional>
#include <ciso646>
#include <type_traits>
#include <memory>
#include <QtCore/qobject.h>
#include <QtGui/qguiapplication.h>
#include <QtWidgets/qapplication.h>

class OPENCVUTILITYSHARED_EXPORT OpenCVUtility :
    public QObject {
    Q_OBJECT
private:
    typedef QObject P;
protected:
    explicit OpenCVUtility(QObject *);
    virtual ~OpenCVUtility();
public:
    static void construct();
    typedef void(* Handle)(QVariant *  );
    typedef void(* HandleQImage)(void *);
    static Handle getHandle();
    static HandleQImage getHandleQImage();
    static cv::Mat read(const QString &);
    static cv::Mat read(const QImage &);
    static QImage read(const cv::Mat &);
    static cv::Mat tryRead(const QImage &);
    static QImage tryRead(const cv::Mat &);
    static QImage getInnerQImage(const cv::Mat & );
    static cv::Mat getInnerOpenCVMat(const QImage & );
    static cv::MatAllocator * getReaderAllocator();
};

inline QString operator""_qs(const char * utf8data__,std::size_t l__) {
    return QString::fromUtf8(utf8data__,l__);
}

#include "OpenCVScene.hpp"
#include "OpenCVItem.hpp"
#include "OpenCVWindow.hpp"
#include "OpenCvStyle.hpp"
#include "OpenCVHistItem.hpp"
#include "ReadOnly.hpp"
#include "OpenCVMatQImage.hpp"
#include "OpenCVQImage.hpp"

#endif // OPENCVUTILITY_HPP
