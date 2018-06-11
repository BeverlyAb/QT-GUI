#include "pathmaker.h"
#include "ui_pathmaker.h"
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

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
    QVector<QPoint> shelfPt;
    QVector<QPoint> pathPt;

    QString in = "";
    //make a pen
    QPen shelfpen;
    shelfpen.setWidth(10);
    shelfpen.setColor(Qt::red);
    painter.setPen(shelfpen);

    //shelf
    in = "/Users/fullstackmachine/Desktop/BevCode/AdvAlg_221/W10/shelf.txt";
    readFile(in, shelfPt);
    painter.drawPoints( shelfPt );

//    //path
    in = "/Users/fullstackmachine/Desktop/BevCode/AdvAlg_221/W10/pathOnly.txt";
    QPen linepen;
    linepen.setWidth(10);
    linepen.setColor(Qt::blue);

    painter.setPen(linepen);
    readFile(in, pathPt);
    painter.drawPoints( pathPt );
}

void PathMaker::readFile(QString in, QVector<QPoint> & polyPoints)
{
    QFile myFile(in);
    if(!myFile.open(QIODevice::ReadOnly))
             QMessageBox::information(0,"info", myFile.errorString());
    QTextStream whole(&myFile);

    QString str = whole.readLine();

    while(!whole.atEnd()){
        QStringList list = str.split(' ');
        int x = list.at(0).toInt();
        int y = list.at(1).toInt();

        if(in == "/Users/fullstackmachine/Desktop/BevCode/AdvAlg_221/W10/pathOnly.txt"){
            xPt.push_back(x);
            yPt.push_back(y);
        }

        //scaling to screen
        x = x *12+10;
        y = y * 12+10;
        polyPoints << QPoint(x,y);
        str = whole.readLine();
    }
    myFile.close();
}

void PathMaker::Route()
{
    QString size= QString::number(xPt.size());

    int hop = 1;
    int dir = UP;
    int prevDir = UP;
    QString term = "";

    for(int i = 0; i < xPt.size() - 1; i++){

        if(xPt[i] != xPt[i + 1]){ //left or right
            if(xPt[i] < xPt[i + 1])
                dir = LEFT;
            else
                dir = RIGHT;
        } else {// traveled up or down
            if(yPt[i] < yPt[i + 1])
                dir = UP;
            else
                dir = DOWN;
        }

        if(dir == prevDir)
            hop++;
        else{
            term += dirToStr(dir) + QString::number(hop) + "\n";
            hop = 1;
            prevDir = dir;
        }
    }

    QMessageBox::information(this, "boxy", term);
}
QString PathMaker::dirToStr(const int & d)
{
    if(d == LEFT)
        return "LEFT ";
    else if(d == RIGHT)
        return "RIGHT ";
    else if(d == UP)
        return "UP ";
    else //default
        return "DOWN ";
}

