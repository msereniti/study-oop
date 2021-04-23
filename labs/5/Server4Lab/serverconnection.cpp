#include "serverconnection.h"

#include <QDebug>
#include <QNetworkDatagram>
#include <QUdpSocket>

ServerConnection::ServerConnection(QObject *parent, const ConnectionInfo &info)
    : QObject(parent) {
  _connection = new QUdpSocket(this);
  _connection->bind(info.bindAddres, info.bindPort,
                    QAbstractSocket::ShareAddress |
                        QAbstractSocket::ReuseAddressHint);

  _sendAddr = info.sendAddres;
  _sendPort = info.sendPort;

  connect(_connection, &QUdpSocket::readyRead, this,
          &ServerConnection::handleOnReadyRead);
}

void ServerConnection::send(QStringList ans) {
  QByteArray data;

  foreach (QString answer, ans) {
    data.append(answer.toUtf8(), answer.size());
    data.append(static_cast<char>(0));
  }

  qDebug() << data.toHex(' ');
  _connection->writeDatagram(data, data.size(), _sendAddr, _sendPort);
}

void ServerConnection::handleOnReadyRead() {
  qDebug() << "new request";
  while (_connection->hasPendingDatagrams()) {
    QNetworkDatagram datagram = _connection->receiveDatagram();
    auto data = datagram.data();
    qDebug() << "received data:";
    qDebug() << data.toHex(' ');
    QDataStream dataStream(data);
    Request req;
    dataStream >> req;
    emit sigReceivedRequest(req);
  }
  qDebug() << "request handled";
}
