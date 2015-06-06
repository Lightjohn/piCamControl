#include "network.h"

network::network()
{

}

void network::initSocket(){
    socket = new QTcpSocket();
    socket->connectToHost(url, 8089);
    socket->waitForConnected();
}

QPixmap network::recvImg(){
    initSocket();
    socket->write("IMG");
    socket->waitForBytesWritten();
    socket->waitForReadyRead();

    QByteArray buffer;
    while (socket->bytesAvailable() > 0)
    {
        buffer.append(socket->readAll());
        socket->waitForReadyRead();
    }
    socket->close();
    QPixmap image;
    image.loadFromData(buffer);
    return image;
}

void network::setPos(int x, int y){
    initSocket();
    QString cmd = "POS "+QString::number(x)+" "+QString::number(y);
    socket->write(cmd.toStdString().c_str());
    socket->flush();
    socket->waitForBytesWritten();
    socket->close();
}

void network::setQuality(int a){
    initSocket();
    QString cmd = "RES ";
    if (a==0) {
        cmd = cmd +"low";
    } else if (a==1) {
        cmd = cmd +"med";
    } else if (a==2) {
        cmd = cmd +"hig";
    }else{
        qDebug() << "Unknown quality";
    }
    socket->write(cmd.toStdString().c_str());
    socket->flush();
    socket->waitForBytesWritten();
    socket->close();
}

void network::connect(QString url){
    this->url = url;
}

network::~network(){
    if(socket != NULL){
        socket->close();
        delete socket;
    }
}
