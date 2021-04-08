#include "controlwindow.h"

TControlWindow::TControlWindow(bool m, QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setFixedSize(200, 130);
  setWindowTitle("Управление");

  setEnabled(m);

  b1 = new QPushButton("Сброс", this);
  b1->setGeometry(10, 10, 180, 20);
  connect(b1, SIGNAL(pressed()), this, SIGNAL(reset()));
  b2 = new QPushButton("Одиночное событие", this);
  b2->setGeometry(10, 40, 180, 20);
  connect(b2, SIGNAL(pressed()), this, SIGNAL(step()));
  b3 = new QPushButton("Автоматический режим", this);
  b3->setGeometry(10, 70, 180, 20);
  connect(b3, SIGNAL(pressed()), this, SLOT(switchMode()));
}

TControlWindow::~TControlWindow() {
  delete b3;
  delete b2;
  delete b1;
}

void TControlWindow::closeEvent(QCloseEvent *event) {
  emit closing();
  event->accept();
}

void TControlWindow::switchMode() {
  bool m = !b1->isEnabled();
  b1->setEnabled(m);
  b2->setEnabled(m);
  b3->setText(m ? "Автоматический режим" : "Ручной режим");
  emit mode(!m);
}
