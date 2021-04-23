#ifndef SERVERCORE_H
#define SERVERCORE_H

#include "serverconnection.h"

#include "polinom.h"
#include <QObject>

class ServerCore : public QObject {
  Q_OBJECT
public:
  explicit ServerCore(QObject *parent = nullptr);

private slots:
  void handleOnNewCalculation(Request req);

private:
  ServerConnection *_connection;
};

#endif // SERVERCORE_H
