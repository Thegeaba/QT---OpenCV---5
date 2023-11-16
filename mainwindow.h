#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QtGui>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QColorDialog>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_loadImage_clicked();

    void on_brn_chooseBackgroundColor_clicked();

    void on_btn_saveImage_clicked();

    void on_slider_thresholdValue_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    Mat background;
    Mat newBackground;

    QString path;
    int backgroundWidth = 576;
    int backgroundHeight = 324;

    Scalar color = Scalar(0, 0, 0);


    Mat selectedROI;
    Rect rectangleROI;

    int thresholdValue = 120;

};
#endif // MAINWINDOW_H
