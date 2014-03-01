#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "dialog.h"
#include<QGraphicsScene>
#include <cv.h>
#include <highgui.h>


using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),ui->progressBar,SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->label->setText("salut!");
    QGraphicsScene *scene = new QGraphicsScene;
    Mat img = imread("/home/lucian/Proiecte/tutorial3/cat.jpg");
 //  QPixmap pixmap("/home/lucian/Proiecte/tutorial3/cat.jpg");

    Laplacian (img,img,CV_8U);

    QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    QPixmap pixmap=QPixmap::fromImage(imgIn);



   scene->addPixmap(pixmap);
   ui->graphicsView->setScene(scene);
   ui->graphicsView->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::warning(this,"titlu","atentie!");
}

void MainWindow::on_pushButton_3_clicked()
{
  Dialog win;
  win.setModal(false);
  win.exec();
}
