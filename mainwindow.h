#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/core/core.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SelectFile_clicked();

    void on_LoadFunctions_clicked();

    void on_Webcam_clicked();

    void on_Iterate_clicked();

    void on_Clear_clicked();

    void on_SaveImage_clicked();

private:
    Ui::MainWindow *ui;
    void show_image(cv::Mat img);
    cv::Mat compute_image(cv::Mat dest);

};

#endif // MAINWINDOW_H
