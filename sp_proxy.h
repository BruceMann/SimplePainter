#ifndef SP_PROXY_H
#define SP_PROXY_H

#include <QObject>
#include<QtNetwork>

class SP_Proxy:public QObject
{
    Q_OBJECT
public:
    explicit SP_Proxy(QObject *parent = nullptr);
    ~SP_Proxy();



public slots:
    void sendDatagram(int mouseAct,int x,int y);
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket = nullptr;

};

#endif // SP_PROXY_H
