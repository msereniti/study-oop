#ifndef APPLICATION_H
#define APPLICATION_H

#include "eventtypes.h"
#include "model.h"
#include "tcpserver.h"
#include <QCoreApplication>

class TApplication : public QCoreApplication {
  Q_OBJECT
  TTcpServer *server;
  TModel *model;
  bool formMessage(QByteArray &, EEvents, void *);

public:
  TApplication(int, char **);
  ~TApplication();
public slots:
  void clientno(int);
  void clientRequest(int, QByteArray);
};

#endif // APPLICATION_H
