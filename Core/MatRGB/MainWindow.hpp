#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP()

#include <QtWidgets/qmainwindow.h>
#include <OpenCVUtility.hpp>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    OpenCVWindow * image_view_;
    OpenCVImageItem::AlgFunctionType alg_;
    std::size_t update_alg_count_=0;
    typedef QMainWindow P;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void addImage();
    void updateAlgFunction();
    void _updateAlgFunction();
};

#endif // MAINWINDOW_HPP
