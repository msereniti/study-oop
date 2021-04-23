#include "clientconnection.h"

#include <QDebug>
#include <QNetworkDatagram>
#include <QUdpSocket>

ClientConnection::ClientConnection(QObject *parent, const ConnectionInfo &info)
    : QObject(parent) {
  _connection = new QUdpSocket(this);
  connect(_connection, &QUdpSocket::readyRead, this,
          &ClientConnection::handleOnReadyRead);
  _connection->bind(info.bindAddres, info.bindPort,
                    QAbstractSocket::ShareAddress |
                        QAbstractSocket::ReuseAddressHint);

  _sendAddr = info.sendAddres;
  _sendPort = info.sendPort;

  _connection->open(QIODevice::ReadWrite);
}

void ClientConnection::send(Request req) {
  QByteArray data;
  QDataStream stream(&data, QIODevice::WriteOnly);
  stream << req;

  _connection->writeDatagram(data, data.size(), _sendAddr, _sendPort);

  qDebug() << "Send";
  qDebug() << data.toHex(' ');
}

void ClientConnection::handleOnReadyRead() {
  QByteArray data;
  int nextPos = 0;
  QString buffer;
  QStringList answer;
  qint16 size = _connection->pendingDatagramSize();

  QNetworkDatagram datagram = _connection->receiveDatagram(size);

  data = datagram.data();

  while (!data.isEmpty()) {
    nextPos = data.indexOf(static_cast<char>(0)) + 1;
    buffer = QString::fromUtf8(data.data(), nextPos);
    answer.append(buffer);
    data.remove(0, buffer.size());
  }

  emit sigReceivedAnswer(answer);
}
