#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

Mat baseImage;
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
    baseImage = imread(fileName.toStdString(),CV_LOAD_IMAGE_COLOR);
    cvtColor(baseImage, baseImage,CV_BGR2RGB);

    show_image(baseImage);
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
    Mat dest=baseImage;

    if(ui->listWidget_2->count()==0)
    {
        QMessageBox::warning(this,"warning","nu ai selectat nicio functie!");
    }

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

    show_image(dest);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget_2->clear();
}
