#include "application.h"

#include <iostream>
using namespace std;

TApplication::TApplication(int argc, char **argv)
    : QCoreApplication(argc, argv) {
  QString port(argv[1]);
  server = new TTcpServer(port.toUInt());
  connect(server, SIGNAL(clientno(int)), this, SLOT(clientno(int)));
  connect(server, SIGNAL(recieve(int, QByteArray)), this,
          SLOT(clientRequest(int, QByteArray)));
  model = new TModel();
}

TApplication::~TApplication() {
  delete model;
  delete server;
}

bool TApplication::formMessage(QByteArray &msg, EEvents type, void *data) {
  TEvents msgData;
  size_t msgLen = sizeof(msgData.type);
  msgData.type = type;
  switch (type) {
  case CLIENTNO:
    msgData.data.no = *((int *)data);
    msgLen += sizeof(msgData.data.no);
    break;
  case PARAMMESSAGE:
    msgData.data.p = *((TParamData *)data);
    msgLen += sizeof(TParamData);
    break;
  case STATEMESSAGE:
    msgData.data.s = *((TStateData *)data);
    msgLen += sizeof(TStateData);
    break;
  default:
    qDebug() << "formMessage error";
    return false;
  }
  msg.clear();
  msg.append(msgLen, ' ');
  memcpy(msg.data(), &msgData, msgLen);
  return true;
}

void TApplication::clientno(int no) {
  QByteArray msg;
  if (formMessage(msg, CLIENTNO, (void *)(&no)))
    server->send(no - 1, msg);
}

void TApplication::clientRequest(int no, QByteArray m) {
  QByteArray msg;
  TParamData pd;
  TStateData sd;
  TEvents msgData;
  memcpy(&msgData, m.data(), m.size());
  qDebug() << "msg type =" << msgData.type;
  switch (msgData.type) {
  case PARAMREQUEST:
    qDebug() << "PARAMREQUEST";
    pd = model->params();
    if (formMessage(msg, PARAMMESSAGE, (void *)(&pd)))
      server->send(no, msg);
    break;
  case PARAMMESSAGE:
    qDebug() << "PARAMMESSAGE";
    model->params() = msgData.data.p;
    break;
  case STATEREQUEST:
    qDebug() << "STATEREQUEST";
    sd = model->states();
    if (formMessage(msg, STATEMESSAGE, (void *)(&sd)))
      server->send(no, msg);
    break;
  case RESET:
    qDebug() << "RESET";
    model->init();
    pd = model->params();
    if (formMessage(msg, PARAMMESSAGE, (void *)(&pd)))
      server->sendAll(msg);
    sd = model->states();
    if (formMessage(msg, STATEMESSAGE, (void *)(&sd)))
      server->sendAll(msg);
    break;
  case TACT:
    qDebug() << "TACT";
    model->tact();
    sd = model->states();
    if (formMessage(msg, STATEMESSAGE, (void *)(&sd)))
      server->sendAll(msg);
    break;
  case ADD_PASSENGER:
    qDebug() << "ADD_PASSENGER";
    model->addPassenger();
    sd = model->states();
    if (formMessage(msg, STATEMESSAGE, (void *)(&sd)))
      server->sendAll(msg);
    break;
  default:
    qDebug() << "unknown message" << msg;
    return;
  }
}
