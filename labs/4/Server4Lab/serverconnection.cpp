#include "serverconnection.h"

#include <QDebug>
#include <QUdpSocket>

ServerConnection::ServerConnection(QObject *parent, const ConnectionInfo &info) :
    QObject(parent)
{
    _connection = new QUdpSocket(this);
    _connection->bind(info.bindAddres, info.bindPort,
                      QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);

    _sendAddr = info.sendAddres;
    _sendPort = info.sendPort;

    connect(_connection, &QUdpSocket::readyRead, this, &ServerConnection::handleOnReadyRead);
}

void ServerConnection::send(QStringList ans)
{
    QByteArray data;

    foreach(QString answer, ans)
    {
        data.append(answer.toUtf8(), answer.size());
        data.append(static_cast<char>(0));
    }

    qDebug() << data.toHex(' ');
    _connection->writeDatagram(data, data.size(), _sendAddr, _sendPort);
}

void ServerConnection::handleOnReadyRead()
{
    qDebug() << "new request";
    QByteArray data;
    Request req;
    qint16 size = _connection->pendingDatagramSize();

    if(size != sizeof (Request))
        return;

    _connection->readDatagram(data.data(), size);

    req = *reinterpret_cast<Request*>(data.data());

    emit sigReceivedRequest(req);
}
