#ifndef NETWORK_H
#define NETWORK_H
#include <QTcpSocket>
#include <QDebug>
#include <QPixmap>

class network
{
public:
    network();
    void connect(QString url);
    QPixmap recvImg();
    void setQuality(int a);
    void setPos(int x, int y);
    ~network();

private:
    void initSocket();
    QTcpSocket *socket;
    QString url;
};

#endif // NETWORK_H
