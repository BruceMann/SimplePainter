#include "sp_proxy.h"

SP_Proxy::SP_Proxy(QObject *parent):QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

SP_Proxy::~SP_Proxy()
{

}

void SP_Proxy::sendDatagram(int mouseAct, int x, int y)
{

}

void SP_Proxy::processPendingDatagrams()
{

}
