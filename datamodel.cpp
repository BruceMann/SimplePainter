#include<QtNetwork>
#include<QtCore>
#include<QDebug>

#include "datamodel.h"

DataModel::DataModel(QObject *parent):
    QObject(parent),
    m_pointData(new PointData)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(55555, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));

    ConnectToServer();
}

DataModel::~DataModel()
{
    delete m_pointData;
    delete udpSocket;
}

void DataModel::ConnectToServer()
{
    QString str = "login";
    QByteArray loginInfo = str.toLatin1();
    udpSocket->writeDatagram(loginInfo,QHostAddress::LocalHost,44444);
}

PointData *DataModel::pointData() const
{
    return m_pointData;
}

void DataModel::broadcastDatagram(float x,float y,int opera,QColor color)
{
    QByteArray datagram = QByteArray::number(x)+","+QByteArray::number(y)+","+QByteArray::number(opera)+","+color.name().toLatin1();
    udpSocket->writeDatagram(datagram,QHostAddress::LocalHost,44444);
}

void DataModel::processPendingDatagrams()
{
    QByteArray datagram;

    while(udpSocket->hasPendingDatagrams()){
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QString data(datagram.constData());
        QStringList strlist = data.split(',');
        float x= strlist[0].toFloat();
        float y= strlist[1].toFloat();
        int op = strlist[2].toInt();
        QColor color = QColor(strlist[3]);
        qDebug()<<"hahhahhaha"<<x<<y<<op<<color;
        m_pointData->setPosX(x);
        m_pointData->setPosY(y);
        m_pointData->setOpera(op);
        m_pointData->setColor(color);
    }
}

PointData::PointData(QObject *parent):
    QObject(parent)
{

}

PointData::PointData(const PointData &other):
    QObject(0),
     m_x(other.m_x),
     m_y(other.m_y),
     m_color(other.m_color),
     m_pixSize(other.m_pixSize),
     m_opera(other.m_opera)
{

}

float PointData::posX() const
{
    return m_x;
}

float PointData::posY() const
{
    return m_y;
}

int PointData::opera() const
{
    return m_opera;
}

QColor PointData::color() const
{
    return m_color;
}

void PointData::setPosX(const float x)
{
    m_x = x;
    emit posChanged();
}

void PointData::setPosY(const float y)
{
    m_y = y;
    emit posChanged();
}

void PointData::setOpera(const int op)
{
    m_opera = op;
}

void PointData::setColor(const QColor cl)
{
    m_color = cl;
}
