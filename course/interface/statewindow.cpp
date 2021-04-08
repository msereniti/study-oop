#include "statewindow.h"
#include "interface.h"

#include <QDebug>

TStateWindow::TStateWindow(QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setFixedSize(200, 130);
  setWindowTitle("Состояние");

  l4 = new QLabel("Состояние:", this);
  l4->setGeometry(10, 10, 180, 20);
  l5 = new QLabel("Состояние1", this);
  l5->setGeometry(10, 35, 100, 20);
  state1 = new QLabel(this);
  state1->setGeometry(110, 35, 30, 20);
  l7 = new QLabel("Состояние2", this);
  l7->setGeometry(10, 60, 100, 20);
  state2 = new QLabel(this);
  state2->setGeometry(110, 60, 30, 20);
}

TStateWindow::~TStateWindow() {
  delete state2;
  delete l7;
  delete state1;
  delete l5;
  delete l4;
}

void TStateWindow::setCurrentState(const TStateData s) {
  qDebug() << "TStateWindow::setCurrentState" << s.r1 << s.r2;
  state1->setText(QString().setNum(s.r1));
  state2->setText(QString().setNum(s.r2));
}

void TStateWindow::closeEvent(QCloseEvent *event) {
  emit closing();
  event->accept();
}
