#include "interface.h"
#include "controlwindow.h"
#include "paramwindow.h"
#include "statewindow.h"

#include <QDebug>

TInterface::TInterface(QWidget *parent) : QWidget(parent) {
  setFixedSize(150, 120);

  canControl = false;

  paramWindow = nullptr;
  stateWindow = nullptr;
  controlWindow = nullptr;

  pbtn = new QPushButton("Параметры", this);
  pbtn->setGeometry(15, 10, 120, 30);
  connect(pbtn, SIGNAL(pressed()), this, SLOT(openParamWindow()));

  sbtn = new QPushButton("Состояние", this);
  sbtn->setGeometry(15, 45, 120, 30);
  connect(sbtn, SIGNAL(pressed()), this, SLOT(openStateWindow()));

  cbtn = new QPushButton("Управление", this);
  cbtn->setGeometry(15, 80, 120, 30);
  connect(cbtn, SIGNAL(pressed()), this, SLOT(openControlWindow()));
}

TInterface::~TInterface() {
  delete cbtn;
  delete pbtn;
  delete sbtn;
}

void TInterface::setControlState(const bool s) {
  canControl = s;
  qDebug() << "interface state" << canControl;
  if (paramWindow != nullptr)
    paramWindow->setEnable(s);
  if (controlWindow != nullptr)
    controlWindow->setEnable(s);
}

void TInterface::setCurrentParams(const TParamData pd) {
  if (paramWindow != nullptr)
    paramWindow->setCurrentParams(pd);
}

void TInterface::setCurrentState(const TStateData sd) {
  if (stateWindow != nullptr)
    stateWindow->setCurrentState(sd);
}

void TInterface::closeEvent(QCloseEvent *event) {
  if (paramWindow != nullptr) {
    disconnect(paramWindow, SIGNAL(closing()), this, SLOT(paramWindowClosed()));
    paramWindow->close();
  }
  if (stateWindow != nullptr) {
    disconnect(stateWindow, SIGNAL(closing()), this, SLOT(stateWindowClosed()));
    stateWindow->close();
  }
  if (controlWindow != nullptr) {
    disconnect(controlWindow, SIGNAL(closing()), this,
               SLOT(controlWindowClosed()));
    controlWindow->close();
  }
  event->accept();
}

void TInterface::paramWindowClosed() {
  disconnect(paramWindow, SIGNAL(closing()), this, SLOT(paramWindowClosed()));
  disconnect(paramWindow, SIGNAL(sendModelParams(TParamData)), this,
             SIGNAL(sendModelParams(TParamData)));
  disconnect(paramWindow, SIGNAL(restoryParams()), this, SLOT(restoryParams()));
  paramWindow = nullptr;
}

void TInterface::stateWindowClosed() {
  disconnect(stateWindow, SIGNAL(closing()), this, SLOT(stateWindowClosed()));
  stateWindow = nullptr;
}

void TInterface::controlWindowClosed() {
  disconnect(controlWindow, SIGNAL(closing()), this,
             SLOT(controlWindowClosed()));
  disconnect(controlWindow, SIGNAL(reset()), this, SIGNAL(reset()));
  disconnect(controlWindow, SIGNAL(step()), this, SIGNAL(step()));
  disconnect(controlWindow, SIGNAL(addPassenger()), this,
             SIGNAL(addPassenger()));
  disconnect(controlWindow, SIGNAL(mode(bool)), this, SIGNAL(mode(bool)));
  controlWindow = nullptr;
}

void TInterface::restoryParams() { emit paramRequest(PARAMREQUEST, nullptr); }

void TInterface::openParamWindow() {
  if (paramWindow == nullptr) {
    paramWindow = new TParamWindow(canControl);
    connect(paramWindow, SIGNAL(sendModelParams(TParamData)), this,
            SIGNAL(sendModelParams(TParamData)));
    connect(paramWindow, SIGNAL(closing()), this, SLOT(paramWindowClosed()));
    connect(paramWindow, SIGNAL(restoryParams()), this, SLOT(restoryParams()));
    paramWindow->show();
    emit paramRequest(PARAMREQUEST, nullptr);
  }
}

void TInterface::openStateWindow() {
  if (stateWindow == nullptr) {
    stateWindow = new TStateWindow();
    connect(stateWindow, SIGNAL(closing()), this, SLOT(stateWindowClosed()));
    stateWindow->show();
    emit stateRequest(STATEREQUEST, nullptr);
  }
}

void TInterface::openControlWindow() {
  if (controlWindow == nullptr) {
    controlWindow = new TControlWindow(canControl);
    connect(controlWindow, SIGNAL(closing()), this,
            SLOT(controlWindowClosed()));
    connect(controlWindow, SIGNAL(reset()), this, SIGNAL(reset()));
    connect(controlWindow, SIGNAL(step()), this, SIGNAL(step()));
    connect(controlWindow, SIGNAL(addPassenger()), this,
            SIGNAL(addPassenger()));
    connect(controlWindow, SIGNAL(mode(bool)), this, SIGNAL(mode(bool)));
    controlWindow->show();
  }
}
