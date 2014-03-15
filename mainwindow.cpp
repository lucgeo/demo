#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "dialog.h"
#include <QGraphicsScene>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace cv;
using namespace std;

Mat img;

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

QGraphicsScene *scene;

void MainWindow::on_pushButton_clicked()
{
    //ui->label->setText("salut!");
    scene = new QGraphicsScene;
     img = imread("/home/lucian/Proiecte/tutorial3/cat.jpg");

     QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    QPixmap pixmap=QPixmap::fromImage(imgIn);

    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    ui->listWidget->addItem("Hello");
    ui->listWidget->addItem("World");
    ui->listWidget->addItem("salut");
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::warning(this,"titlu","atentie!");


}

void MainWindow::on_pushButton_3_clicked()
{
    QList<QListWidgetItem*> selected = ui->listWidget_2->selectedItems();
    if(selected.count() > 0){

        Point p(10,20);
        string s =  selected[0]->text().toUtf8().constData();
        putText(img,s, p,FONT_HERSHEY_SCRIPT_SIMPLEX,2,Scalar::all(255));

        QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
       QPixmap pixmap=QPixmap::fromImage(imgIn);

       scene->addPixmap(pixmap);
       ui->graphicsView->setScene(scene);
       ui->graphicsView->show();
    }
}
