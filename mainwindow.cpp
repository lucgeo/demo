#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

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

    ui->FunctionList->addItem("Red");
    ui->FunctionList->addItem("Green");
    ui->FunctionList->addItem("Blue");
    ui->FunctionList->addItem("Blur");
    ui->FunctionList->addItem("toGray");
    ui->FunctionList->addItem("toRGB");
    ui->FunctionList->addItem("Flip X");
    ui->FunctionList->addItem("Flip Y");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::show_image(Mat img)
{
    QImage image=QImage((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    QPixmap pixmap=QPixmap::fromImage(image);

    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

Mat MainWindow::compute_image(Mat d)
{
    Mat dest;
    d.copyTo(dest);

    if(ui->SelectedFunction->count()==0)
    {
        QMessageBox::warning(this,"warning","nu ai selectat nicio functie!");
    }

    for(int i = 0; i < ui->SelectedFunction->count(); i++)
    {
        /*inherit qlist widget in a class8*/


        QListWidgetItem* item = ui->SelectedFunction->item(i);
        if(! item->text().compare("Blur"))
        {
            medianBlur(dest,dest,13);
        }

        if(!item->text().compare("Red"))
        {
            Mat temp[3];
            split(dest,temp);
            dest = temp[0];
        }

        if(!item->text().compare("Green"))
        {
            Mat temp[3];
            split(dest,temp);
            dest = temp[1];
        }

        if(!item->text().compare("Blue"))
        {
            Mat temp[3];
            split(dest,temp);
            dest = temp[2];
        }

        if(!item->text().compare("toGray"))
        {
            cvtColor(dest,dest,CV_RGB2GRAY);
        }

        if(!item->text().compare("toRGB"))
        {
            cvtColor(dest,dest,CV_GRAY2RGB);
        }

        if(!item->text().compare("Flip X"))
        {
            flip(dest,dest,0);
        }

        if(!item->text().compare("Flip Y"))
        {
            flip(dest,dest,1);
        }
    }

    if(dest.channels() == 1){
        cvtColor(dest, dest, CV_GRAY2RGB);
    }

    return dest;
}



void MainWindow::on_SelectFile_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "~", tr("Images (*.png *.xpm *.jpg)"));

    if( fileName.length() > 0)
    {
        scene = new QGraphicsScene;
        baseImage = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
        cvtColor(baseImage, baseImage, CV_BGR2RGB);

        show_image(baseImage);
    }
}

void MainWindow::on_Iterate_clicked()
{
    Mat dest;

    dest=compute_image(baseImage);

    show_image(dest);
}


void MainWindow::on_Clear_clicked()
{
    QList<QListWidgetItem*> selected=ui->SelectedFunction->selectedItems();
    for(int i=0; i<selected.length(); i++)
    {
        delete selected[i];
    }
}

void MainWindow::on_Webcam_clicked()
{
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        QMessageBox::warning(this, "webcam", "camera nu poate fi pornita");
    }
    else
    {
        cap>>baseImage;
        show_image(baseImage);
    }
}

void MainWindow::on_SaveImage_clicked()
{
    Mat img = compute_image(baseImage);
    cvtColor(img, img, CV_RGB2BGR);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "result.png", tr("Images (*.jpg)"));
    string imageName=fileName.toUtf8().constData();
    if( imageName.length() > 0)
    imwrite(imageName, img);
}
