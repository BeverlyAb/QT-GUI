#include "pathmaker.h"
#include "ui_pathmaker.h"

PathMaker::PathMaker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PathMaker)
{
    ui->setupUi(this);
}

PathMaker::~PathMaker()
{
    delete ui;
}
void PathMaker::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    //path
    QVector<QPoint> polyPoints;
    QString all = "/Users/fullstackmachine/Desktop/BevCode/AdvAlg_221/W10/trash.txt";
    QFile myFile(all);

    if(!myFile.open(QIODevice::ReadOnly))
             QMessageBox::information(0,"info", myFile.errorString());
    QTextStream whole(&myFile);

    QString str = whole.readLine();
    while(!whole.atEnd()){
        QStringList list = str.split(' ');
        int x = list.at(0).toInt()*10 + 10;
        int y = list.at(1).toInt()*10 + 10;
        polyPoints << QPoint(x,y);
        str = whole.readLine();
    }
    myFile.close();

    //make a pen
    QPen linepen;
    linepen.setWidth(4);
    linepen.setColor(Qt::red);
    painter.setPen(linepen);
    //
    QVector<QPoint> linePoints;
    foreach( QPoint point, polyPoints )
        linePoints << point;
    painter.drawLines( linePoints );

}

//void PathMaker::readFile()
//{
//    QString all = "/Users/fullstackmachine/Desktop/BevCode/AdvAlg_221/W10/trash.txt";
//    QFile myFile(all);
//    if(!myFile.open(QIODevice::ReadOnly))
//             QMessageBox::information(0,"info", myFile.errorString());
//    QTextStream whole(&myFile);

//    QString str = whole.readLine();
//    while(!whole.atEnd()){
//        QStringList list = str.split(' ');
//        int x = list.at(0).toInt();
//        int y = list.at(1).toInt();
//        polyPoints << QPoint(x,y);
//    }
//    myFile.close();
//}
