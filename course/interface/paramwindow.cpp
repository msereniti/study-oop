#include "paramwindow.h"

#include <QDebug>

TParamWindow::TParamWindow(bool m, QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setWindowTitle("Параметры");
  setFixedSize(200, 130);

  setEnabled(m);

  l1 = new QLabel("Модуль:", this);
  l1->setGeometry(10, 10, 100, 20);
  modulo = new QSpinBox(this);
  modulo->setRange(2, 200);
  modulo->setGeometry(110, 10, 50, 20);
  l2 = new QLabel("Шаг 1", this);
  l2->setGeometry(10, 35, 100, 20);
  param1 = new QSpinBox(this);
  param1->setRange(-100, 100);
  param1->setGeometry(110, 35, 50, 20);
  l3 = new QLabel("Шаг 2", this);
  l3->setGeometry(10, 60, 100, 20);
  param2 = new QSpinBox(this);
  param2->setRange(-100, 100);
  param2->setGeometry(110, 60, 50, 20);
  b = new QPushButton("Применить", this);
  b->setGeometry(10, 90, 85, 30);
  connect(b, SIGNAL(pressed()), this, SLOT(setModelParam()));
  r = new QPushButton("Отменить", this);
  r->setGeometry(105, 90, 85, 30);
  connect(r, SIGNAL(pressed()), this, SIGNAL(restoryParams()));
}

TParamWindow::~TParamWindow() {
  delete r;
  delete b;
  delete param2;
  delete l3;
  delete param1;
  delete l2;
  delete modulo;
  delete l1;
}

void TParamWindow::closeEvent(QCloseEvent *event) {
  emit closing();
  event->accept();
}

void TParamWindow::setModelParam() {
  TParamData pd;
  pd.m = modulo->value();
  pd.p1 = param1->value();
  pd.p2 = param2->value();
  emit sendModelParams(pd);
}

void TParamWindow::setCurrentParams(const TParamData pd) {
  qDebug() << "TParamWindow::setCurrentParams";
  modulo->setValue(pd.m);
  param1->setValue(pd.p1);
  param2->setValue(pd.p2);
}
