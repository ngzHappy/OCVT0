#ifndef OPENCVWINDOW_HPP
#define OPENCVWINDOW_HPP() 1

#include <QtWidgets/qgraphicsview.h>
#include "OpenCVScene.hpp"
#include "opencvutility_global.hpp"

class OPENCVUTILITYSHARED_EXPORT OpenCVWindow : public QGraphicsView {
    Q_OBJECT
private:
    typedef QGraphicsView P;
    OpenCVScene * const scene_;
public:
    explicit OpenCVWindow(QWidget * parent=nullptr);
    virtual ~OpenCVWindow();

    template<typename B,typename E>
    OpenCVHistItem * insertHist(B,E);
    OpenCVHistItem * insertHist(QList<qreal> data_) { return scene_->insertHist(std::move(data_)); }
    virtual OpenCVImageItem * insertImage(QImage i) { return scene_->insertImage(std::move(i)); }
    void setImageAlg(const OpenCVImageItem::AlgFunctionType &);
protected:
    void resizeEvent(QResizeEvent *event) override;
};

template<typename B,typename E>
OpenCVHistItem * OpenCVWindow::insertHist(B b,E e) {
    return scene_->insertHist<B,E>(b,e);
}

#endif // OPENCVWINDOW_HPP
