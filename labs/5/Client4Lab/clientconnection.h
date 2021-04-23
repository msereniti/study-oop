#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QHostAddress>
#include <QObject>

struct Request {
  int aCoef = 0;
  int bCoef = 0;
  int cCoef = 0;
  int xVarible = 0;
  int mode = 0;

  friend QDataStream &operator<<(QDataStream &out, const Request &req) {
    out << req.aCoef;
    out << req.bCoef;
    out << req.cCoef;
    out << req.xVarible;
    out << req.mode;
    return out;
  }
  friend QDataStream &operator>>(QDataStream &in, Request &req) {
    in >> req.aCoef;
    in >> req.bCoef;
    in >> req.cCoef;
    in >> req.xVarible;
    in >> req.mode;
    return in;
  }
};

struct ConnectionInfo {
  QHostAddress bindAddres = QHostAddress();
  qint16 bindPort = 0;
  QHostAddress sendAddres = QHostAddress();
  qint16 sendPort = 0;
};

class QUdpSocket;
class ClientConnection : public QObject {
  Q_OBJECT
public:
  explicit ClientConnection(QObject *parent = nullptr,
                            const ConnectionInfo &info = ConnectionInfo());

  void send(Request req);

signals:
  void sigReceivedAnswer(QStringList results);

private slots:
  void handleOnReadyRead();

private:
  QUdpSocket *_connection;

  QHostAddress _sendAddr;
  qint16 _sendPort = 0;
};

#endif // CLIENTCONNECTION_H
