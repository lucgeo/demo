#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "dialog.h"
#include <QGraphicsScene>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QFileDialog>

#include <iostream>
using namespace cv;
using namespace std;

Mat img;
QGraphicsScene *scene;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
 QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/lucian/", tr("Images (*.png *.xpm *.jpg)"));

    scene = new QGraphicsScene;
    img = imread(fileName.toStdString(),CV_LOAD_IMAGE_COLOR);
        Mat dest ;

        cvtColor(img, dest,CV_BGR2RGB);

        QImage image=QImage((uchar*)dest.data, dest.cols, dest.rows,  img.step,QImage::Format_RGB888);

    QPixmap pixmap=QPixmap::fromImage(image);

    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->addItem("Red");
    ui->listWidget->addItem("Green");
    ui->listWidget->addItem("Blue");


}

void MainWindow::on_pushButton_3_clicked()
{


   for(int i = 0; i < ui->listWidget_2->count(); i++)
   {
       QListWidgetItem* item = ui->listWidget_2->item(i);
       QMessageBox::warning(this,"titlu","atentie!");
   }
//inRange(img,Scalar(0,255,0),Scalar(255,255,255),img);

        QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
       QPixmap pixmap=QPixmap::fromImage(imgIn);

       scene->addPixmap(pixmap);
       ui->graphicsView->setScene(scene);
       ui->graphicsView->show();

}
