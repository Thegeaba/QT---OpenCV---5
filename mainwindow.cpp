#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_loadImage_clicked()
{
    path = QFileDialog::getOpenFileName(this, "Selectați o imagine", QDir::homePath(), "Imagini (*.png *.jpg *.jpeg)");

        if (!path.isEmpty()) {
        background = imread(path.toStdString());
        cv::resize(background, background, Size(backgroundWidth, backgroundHeight));

        QString tempImagePath = "background.jpg";
        imwrite(tempImagePath.toStdString(), background);

        ui->frame_selectedROI->setStyleSheet("background-image: url(" + tempImagePath + ");");
        ui->frame_mainObj->setStyleSheet("background-image: url(" + tempImagePath + ");");

    }
}

void MainWindow::on_brn_chooseBackgroundColor_clicked()
{
    if(!path.isEmpty()){
        QColor newColor = QColorDialog::getColor(QColor(color[0], color[1], color[2]), this);
        if (newColor.isValid()) {
            color = Scalar(newColor.blue(), newColor.green(), newColor.red());
        }

        QString cssColor = QString("background-color: rgb(%1, %2, %3);").arg(color[2]).arg(color[1]).arg(color[0]);
        ui->frame_choosenBackgroundColor->setStyleSheet(cssColor);
    }
}

void MainWindow::on_btn_saveImage_clicked()
{
    if (!path.isEmpty()) {
        cv::imwrite("C:/Users/Cristi/Desktop/img mea.jpg", newBackground);
    }
}

void MainWindow::on_slider_thresholdValue_valueChanged(int value)
{

    if (!path.isEmpty()) {
        thresholdValue = value;

        rectangleROI = cv::Rect(300, 10, 190, 280);

        cv::Mat imageWithROI = background.clone();
        cv::rectangle(imageWithROI, rectangleROI, color, 2);

        selectedROI = background(rectangleROI);

        cv::Mat newROI = cv::Mat::zeros(selectedROI.size(), selectedROI.type());
        newROI.setTo(color);

        cv::Mat roiGray;
        cv::cvtColor(selectedROI, roiGray, cv::COLOR_BGR2GRAY);

        cv::Mat thresholded;
        cv::threshold(roiGray, thresholded, thresholdValue, 255, cv::THRESH_BINARY_INV);

        cv::Mat dilated;
        cv::dilate(thresholded, dilated, cv::Mat(), cv::Point(-1, -1), 4);

        cv::Mat eroded;
        cv::erode(dilated, eroded, cv::Mat(), cv::Point(-1, -1), 1);

        selectedROI.copyTo(newROI, eroded);

        std::string tempImagePath = "temp_image.png";
        cv::imwrite(tempImagePath, imageWithROI);

        newBackground = Mat(backgroundHeight, backgroundWidth, CV_8UC3, color);

        newROI.copyTo(newBackground(rectangleROI));

        string tempNewBackground = "temp_newBackground.png";
        imwrite(tempNewBackground, newBackground);

        string tempThresholded = "temp_thresholded.png";
        imwrite(tempThresholded, thresholded);

        string tempDilated = "temp_dilated.png";
        imwrite(tempDilated, dilated);

        string tempEroded = "temp_eroded.png";
        imwrite(tempEroded, eroded);

        string tempNewROI = "temp_newROI.png";
        imwrite(tempNewROI, newROI);

        QString styleSheet = "background-image: url(" + QString::fromStdString(tempNewBackground) + ");";
        ui->frame_selectedROI->setStyleSheet(styleSheet);

        QString styleSheet1 = "background-image: url(" + QString::fromStdString(tempImagePath) + ");";
        ui->frame_mainObj->setStyleSheet(styleSheet1);

        QString styleSheet2 = "background-image: url(" + QString::fromStdString(tempThresholded) + ");";
        ui->frame_thresholded->setStyleSheet(styleSheet2);

        QString styleSheet3 = "background-image: url(" + QString::fromStdString(tempDilated) + ");";
        ui->frame_dilated->setStyleSheet(styleSheet3);

        QString styleSheet4 = "background-image: url(" + QString::fromStdString(tempEroded) + ");";
        ui->frame_eroded->setStyleSheet(styleSheet4);

        QString styleSheet5 = "background-image: url(" + QString::fromStdString(tempNewROI) + ");";
        ui->frame_newROI->setStyleSheet(styleSheet5);
    }
}
