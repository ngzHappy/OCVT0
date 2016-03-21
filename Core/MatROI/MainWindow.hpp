#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP()

#include <OpenCVUtility.hpp>

class MainWindow : public OpenCVWindow
{
    Q_OBJECT
private:
    typedef OpenCVWindow P;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    OpenCVImageItem * insertImage(QImage i)override;
};

#endif // MAINWINDOW_HPP
