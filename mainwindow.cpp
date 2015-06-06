#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
{
    QGridLayout *layout = new QGridLayout();
    img = new QLabel("IMAGE");
    img->setPixmap(QPixmap("test.png"));

    upb = new QPushButton("UP");
    downb = new QPushButton("DOWN");
    rightb = new QPushButton("RIGHT");
    leftb = new QPushButton("LEFT");
    refreshb = new QPushButton("Refresh");

    qualityb = new QComboBox();
    qualityb->addItem("High");
    qualityb->addItem("Medium");
    qualityb->addItem("Low");

    layout->addWidget(img,0,1);
    layout->addWidget(upb,1,1);
    layout->addWidget(downb,3,1);
    layout->addWidget(rightb,2,2);
    layout->addWidget(leftb,2,0);
    layout->addWidget(qualityb,4,2);
    layout->addWidget(refreshb,5,1);

    QObject::connect(upb,SIGNAL(clicked()),this, SLOT(up()));
    QObject::connect(downb,SIGNAL(clicked()),this, SLOT(down()));
    QObject::connect(rightb,SIGNAL(clicked()),this, SLOT(right()));
    QObject::connect(leftb,SIGNAL(clicked()),this, SLOT(left()));
    QObject::connect(qualityb,SIGNAL(activated(QString)),this, SLOT(quality(QString)));
    QObject::connect(refreshb,SIGNAL(clicked()),this, SLOT(refresh()));

    setLayout(layout);

    net = new network();
    net->connect("localhost");

    limit_x_left = 60;
    limit_x_right = 240;
    limit_y_bottom = 80;
    limit_y_top = 180;
    x = 128;
    y = 140;
    inc = 10;
}

void MainWindow::up(){
    y -= inc;
    net->setPos(x,y);
    qDebug() <<"up";
}
void MainWindow::down(){
    y += inc;
    net->setPos(x,y);
    qDebug() <<"down";
}
void MainWindow::right(){
    x += inc;
    net->setPos(x,y);
    qDebug() <<"right";
}
void MainWindow::left(){
    x -= inc;
    net->setPos(x,y);
    qDebug() <<"left";
}
void MainWindow::quality(QString text){
    if (text.compare("High") == 0 ) {
        net->setQuality(2);
    } else if (text.compare("Medium") == 0 ) {
        net->setQuality(1);
    }else if (text.compare("Low") == 0 ){
        net->setQuality(0);
    } else {
        qDebug() <<"ERREOR res "<<text;
    }
    qDebug() <<"quality "<<text;
}
void MainWindow::refresh(){
    qDebug() <<"Refreshing";
    img->setPixmap(net->recvImg());
}

MainWindow::~MainWindow()
{
}
