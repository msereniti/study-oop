#ifndef APPLICATION_H
#define APPLICATION_H

#include "generator.h"
#include "interface.h"
#include "tcpclient.h"
#include <QApplication>
#include <QObject>

class TApplication : public QApplication {
  Q_OBJECT

  TTcpClient *client;
  TInterface *interface;
  TEventGenerator *generator;

public:
  TApplication(int, char **);
  ~TApplication();
public slots:
  void toModel(EEvents, void *);
  void fromModel(QByteArray);
  void sendModelParams(TParamData);
  void reset();
  void step();
  void addPassenger();
  void mode(bool);
};

#endif // APPLICATION_H
