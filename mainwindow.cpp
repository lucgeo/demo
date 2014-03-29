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


void MainWindow::show_image(Mat img)
{
    cvtColor(img, img,CV_BGR2RGB);

    QImage image=QImage((uchar*)img.data, img.cols, img.rows,  img.step,QImage::Format_RGB888);

QPixmap pixmap=QPixmap::fromImage(image);

scene->addPixmap(pixmap);
ui->graphicsView->setScene(scene);
ui->graphicsView->show();

}



void MainWindow::on_pushButton_clicked()
{

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
 QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/lucian/Proiecte/tutorial3", tr("Images (*.png *.xpm *.jpg)"));

    scene = new QGraphicsScene;
    img = imread(fileName.toStdString(),CV_LOAD_IMAGE_COLOR);


        show_image(img);

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->addItem("Red");
    ui->listWidget->addItem("Green");
    ui->listWidget->addItem("Blue");
    ui->listWidget->addItem("Blur");
    ui->listWidget->addItem("toGray");
    ui->listWidget->addItem("toRGB");


}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->listWidget_2->count()==0)
        QMessageBox::warning(this,"warning","nu ai selectat nicio functie!");
Mat dest=img;
   for(int i = 0; i < ui->listWidget_2->count(); i++)
   {

       QListWidgetItem* item = ui->listWidget_2->item(i);
       if(! item->text().compare("Blur")){
           medianBlur(dest,dest,13); }

       if(!item->text().compare("Red"))
       {
           inRange(dest,Scalar(0,0,0),Scalar(0,0,255),dest);
       }

       if(!item->text().compare("toGray"))
       {
           cvtColor(dest,dest,CV_RGB2GRAY);
       }

       if(!item->text().compare("toRGB"))
       {
           cvtColor(dest,dest,CV_GRAY2RGB);
       }
   }

//inRange(img,Scalar(127,127,127),Scalar(255,255,255),img);
//QMessageBox::warning(this,"titlu","red");}

show_image(dest);

}


void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget_2->clear();
}
