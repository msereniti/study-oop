#include "statewindow.h"
#include "interface.h"

#include <QDebug>

TStateWindow::TStateWindow(QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setFixedSize(200, 300);
  setWindowTitle("Состояние");

  timePassedLabel = new QLabel("Внутреннее время:", this);
  timePassedLabel->setGeometry(10, 10, 180, 20);
  timePassedValueLabel = new QLabel("-", this);
  timePassedValueLabel->setGeometry(10, 30, 180, 20);
  rejectedPassengersLabel = new QLabel("Отклоненных пассажиров:", this);
  rejectedPassengersLabel->setGeometry(10, 50, 180, 20);
  rejectedPassengersValueLabel = new QLabel("-", this);
  rejectedPassengersValueLabel->setGeometry(10, 70, 180, 20);
  beforeQueueLabel = new QLabel("Пассажиры вне очередей:", this);
  beforeQueueLabel->setGeometry(10, 90, 180, 20);
  beforeQueueValueLabel = new QLabel("-", this);
  beforeQueueValueLabel->setGeometry(10, 110, 180, 20);
  queueLabel = new QLabel("Очереди в кассы:", this);
  queueLabel->setGeometry(10, 130, 180, 20);
  queueTextEdit = new QTextEdit("-", this);
  queueTextEdit->setGeometry(10, 150, 180, 130);
  queueTextEdit->setReadOnly(true);

  // l4 = new QLabel("Состояние:", this);
  // l4->setGeometry(10, 10, 180, 20);
  // l5 = new QLabel("Состояние1", this);
  // l5->setGeometry(10, 35, 100, 20);
  // state1 = new QLabel(this);
  // state1->setGeometry(110, 35, 30, 20);
  // l7 = new QLabel("Состояние2", this);
  // l7->setGeometry(10, 60, 100, 20);
  // state2 = new QLabel(this);
  // state2->setGeometry(110, 60, 30, 20);
}

TStateWindow::~TStateWindow() { delete timePassedLabel; }

void TStateWindow::setCurrentState(const TStateData state) {
  // qDebug() << "TStateWindow::setCurrentState" << state;
  timePassedValueLabel->setText(QString().setNum(state.timePassed));
  rejectedPassengersValueLabel->setText(
      QString().setNum(state.rejectedPassengers));
  beforeQueueValueLabel->setText(
      QString().setNum(state.passengersToBeDistributed));

  QString queuesText = "";

  for (int i = 0; i < state.queuesCount; i++) {
    queuesText += "очередь " + QString().setNum(i + 1) + ": " +
                  QString().setNum(state.queues[i].passengersCount) +
                  " пассажиров\n";
  }

  qDebug() << queuesText;
  qDebug() << state.queuesCount;

  queueTextEdit->setText(queuesText);
}

void TStateWindow::closeEvent(QCloseEvent *event) {
  emit closing();
  event->accept();
}
