#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile myFile("/Users/fullstackmachine/Desktop/BevCode/AdvAlg_221/W9/trash2.txt");
       if(!myFile.open(QIODevice::ReadOnly))
           QMessageBox::information(0,"info", myFile.errorString());

    QTextStream in(&myFile);
    QString coord = "";


    QRegExp rx("[\\W+]"); //match '(' ',' ')' and remove '\t'

    QString str = in.readLine();
    //skip to path of first order
    for(int i = 0; i < 5; i++){
        str = in.readLine();
    }

    while(!in.atEnd())
    {
    //    qDebug() << qPrintable(str);
        QStringList list = str.split(rx, QString::SkipEmptyParts);

        QString name = list.at(0);
       // qDebug() << "--------------LIST-------------\n";
       // qDebug() << list;

        QList <int> nums;
        //start at 4 to exclude Item #, Hop #,
        //Weight Tens, Weight Tenths,  Effort Tens, Effort Tenths
        for(int i = 6; i < list.size(); i++)
        {
            nums.append(list.at(i).toInt());
        }
        //qDebug() << "2--------------NUMS------------\n";

        if(nums.size() > 1) { // exclude the last 0 from "total effort..."
            for(int i = 0; i < nums.size(); i++)
            {
                qDebug() << qPrintable("num" + QString::number(i+1) + ":") << nums.at(i);
            }
        }
        list.clear();
        str = in.readLine();
        qDebug() << "------------------------------\n";
    }
    myFile.close();
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::blue);


    ui->label->setAutoFillBackground(true);
    ui->label->setPalette(sample_palette);
    //ui->label_145->setText("What ever text");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}
