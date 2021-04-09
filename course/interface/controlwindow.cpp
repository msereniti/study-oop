#include "controlwindow.h"

TControlWindow::TControlWindow(bool realTimeMode, QWidget *parent)
    : QWidget(parent) {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setFixedSize(200, 140);
  setWindowTitle("Управление");

  setEnabled(realTimeMode);

  resetBtn = new QPushButton("Сброс", this);
  resetBtn->setGeometry(10, 10, 180, 30);
  connect(resetBtn, SIGNAL(pressed()), this, SIGNAL(reset()));
  nextStepBtn = new QPushButton("Следующая секунда", this);
  nextStepBtn->setGeometry(10, 40, 180, 30);
  connect(nextStepBtn, SIGNAL(pressed()), this, SIGNAL(step()));
  addPassengerBtn = new QPushButton("Добавить пассажира", this);
  addPassengerBtn->setGeometry(10, 70, 180, 30);
  connect(addPassengerBtn, SIGNAL(pressed()), this, SIGNAL(addPassenger()));
  realTimeBtn = new QPushButton("Пошаговое время", this);
  realTimeBtn->setGeometry(10, 100, 180, 30);
  connect(realTimeBtn, SIGNAL(pressed()), this, SLOT(switchMode()));
}

TControlWindow::~TControlWindow() {
  delete resetBtn;
  delete nextStepBtn;
  delete addPassengerBtn;
  delete realTimeBtn;
}

void TControlWindow::closeEvent(QCloseEvent *event) {
  emit closing();
  event->accept();
}

void TControlWindow::switchMode() {
  bool realTimeMode = nextStepBtn->isEnabled();
  resetBtn->setEnabled(!realTimeMode);
  nextStepBtn->setEnabled(!realTimeMode);
  realTimeBtn->setText(realTimeMode ? "Реальное время" : "Пошаговое время");
  emit mode(realTimeMode);
}
