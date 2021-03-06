﻿#include "MainWindow.hpp"
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qslider.h>
#include <QtCore/qdebug.h>
#include <OpenCVUtility.hpp>
#include <QtCore/qtimer.h>
/*亮度 红绿 蓝黄*/

namespace {
namespace __private {

class CentralWidget :public QWidget {
public:
    class Line_ {
    public:
        QDoubleSpinBox * spinBox_;
        QSlider * slider_;
        void create(QVBoxLayout * l);
    };
    Line_ L_,A_,B_;
    QVBoxLayout * layout_;

    CentralWidget();
};

void CentralWidget::Line_::create(QVBoxLayout * l) {
    {
        QHBoxLayout * l_=new QHBoxLayout;
        l_->setMargin(0);
        l_->setSpacing(0);
        l->addLayout(l_);
        spinBox_=new QDoubleSpinBox;
        l_->addWidget(spinBox_);
        slider_=new QSlider(Qt::Horizontal);
        l_->addWidget(slider_);

        spinBox_->setMinimum(0);
        spinBox_->setMaximum(10);
        spinBox_->setSingleStep(0.01);
        spinBox_->setValue(1);

        slider_->setMinimum(0);
        slider_->setMaximum(1000);
        slider_->setSingleStep(1);
        slider_->setValue(100);

        typedef void(QDoubleSpinBox::* TT)(double );
        QObject::connect(spinBox_,TT(&QDoubleSpinBox::valueChanged),
            slider_,[this](double v) {slider_->setValue(qRound(v*100));});
        QObject::connect(slider_,&QSlider::valueChanged,
            spinBox_,[this](int v) { spinBox_->setValue(double(v)/(100.0)); });
    }
}

CentralWidget::CentralWidget() {
    {
        layout_=new QVBoxLayout;
        layout_->setMargin(0);
        layout_->setSpacing(0);
        this->setLayout(layout_);
        L_.create(layout_);
        A_.create(layout_);
        B_.create(layout_);
    }
}

}
}


MainWindow::MainWindow(QWidget *parent)
    : P(parent) {
    image_view_=new OpenCVWindow;
    __private::CentralWidget * cwidget_=new __private::CentralWidget;
    cwidget_->layout_->addWidget(image_view_);
    this->setCentralWidget(cwidget_);
    this->resize(768,512);

    QMenuBar * mbar_=menuBar();
    QAction * action_=mbar_->addAction(u8R"(选择图片)"_qs);
    connect(action_,&QAction::triggered,
        this,[this](bool) {addImage();});

    typedef void(QDoubleSpinBox::* TT)(double );
    connect(cwidget_->L_.spinBox_,TT(&QDoubleSpinBox::valueChanged),
        this,[this](double) {updateAlgFunction(); });
    connect(cwidget_->A_.spinBox_,TT(&QDoubleSpinBox::valueChanged),
        this,[this](double) {updateAlgFunction(); });
    connect(cwidget_->B_.spinBox_,TT(&QDoubleSpinBox::valueChanged),
        this,[this](double) {updateAlgFunction(); });
}

/*避免过于频繁的调用*/
void MainWindow::updateAlgFunction() {
    auto id__= ++update_alg_count_;
    QTimer::singleShot(5,this,[this,id__]() {
        if (id__==update_alg_count_) {
            _updateAlgFunction();
        }
    }
    );
}

void MainWindow::_updateAlgFunction() {

    /*获得窗口*/
    __private::CentralWidget * cw_
        = dynamic_cast<__private::CentralWidget *>(centralWidget());

    /*获得Lab缩放值*/
    double sl_,sa_,sb_;
    sl_ = cw_->L_.spinBox_->value();
    sa_ = cw_->A_.spinBox_->value();
    sb_ = cw_->B_.spinBox_->value();

    /*生成函数*/
    alg_=OpenCVImageItem::AlgFunctionType(
        new std::function< QImage(const QImage &) >{
        [sl_,sa_,sb_](const QImage & image_)->QImage {
        if (image_.width()<=0) { return image_; }
        if (image_.height()<=0) { return image_; }
        auto cvMat_ = qImage2CVmat(image_.convertToFormat(QImage::Format_RGB888));
        cv::Mat cvMatLAB_;
        cv::cvtColor(cvMat_.first,cvMatLAB_,CV_RGB2Lab);
        std::vector<cv::Mat> Lab_;
        cv::split(cvMatLAB_,Lab_);
        if(Lab_.size()>=3){
            Lab_[0]*=sl_;Lab_[1]*=sa_;Lab_[2]*=sb_;
            cv::merge(Lab_,cvMatLAB_);
            cv::cvtColor(cvMatLAB_,cvMat_.first,CV_Lab2RGB);
            return cvMat_.second;
        }
        return image_;
    }
    }
        );

    /*设置函数*/
    image_view_->setImageAlg(alg_);
}

void MainWindow::addImage() {

    QStringList files_= QFileDialog::getOpenFileNames(
            this,
            u8R"(选择图片)"_qs,
            ""/*dir*/,
            ""/*filter*/
            );

    for (const auto & i:files_) {
        image_view_->insertImage(QImage(i))->setAlgFunction(alg_);
    }

}

MainWindow::~MainWindow() {

}




