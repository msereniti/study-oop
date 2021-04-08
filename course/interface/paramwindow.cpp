#include "paramwindow.h"

#include <QDebug>

TParamWindow::TParamWindow(bool m, QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setWindowTitle("Параметры");
  setFixedSize(300, 130);

  setEnabled(m);

  l1 = new QLabel("Число окон кассы (N):", this);
  l1->setGeometry(10, 10, 200, 20);
  slotsCount_n = new QSpinBox(this);
  slotsCount_n->setRange(0, 99999);
  slotsCount_n->setGeometry(210, 10, 50, 20);
  l2 = new QLabel("Макс. длинна очереди (M):", this);
  l2->setGeometry(10, 35, 200, 20);
  maxQueue_m = new QSpinBox(this);
  maxQueue_m->setRange(0, 99999);
  maxQueue_m->setGeometry(210, 35, 50, 20);
  l3 = new QLabel("Время обслуживания:", this);
  l3->setGeometry(10, 60, 200, 20);
  handlingTime = new QSpinBox(this);
  handlingTime->setRange(0, 99999);
  handlingTime->setGeometry(210, 60, 50, 20);
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
  delete slotsCount_n;
  delete l3;
  delete maxQueue_m;
  delete l2;
  delete handlingTime;
  delete l1;
}

void TParamWindow::closeEvent(QCloseEvent *event) {
  emit closing();
  event->accept();
}

void TParamWindow::setModelParam() {
  TParamData pd;
  pd.slotsCount_n = slotsCount_n->value();
  pd.maxQueue_m = maxQueue_m->value();
  pd.handlingTime = handlingTime->value();
  emit sendModelParams(pd);
}

void TParamWindow::setCurrentParams(const TParamData pd) {
  qDebug() << "TParamWindow::setCurrentParams";
  slotsCount_n->setValue(pd.slotsCount_n);
  maxQueue_m->setValue(pd.maxQueue_m);
  handlingTime->setValue(pd.handlingTime);
}
