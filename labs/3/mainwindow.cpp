#include "mainwindow.h"
#include "./polinom.h"
#include "./ui_mainwindow.h"
#include "cstring"
#include <sstream>

Polinom *polynomial = new Polinom();
double resolveBy = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() { QCoreApplication::exit(); }

void MainWindow::updateUi() {
  PolynomialRoots roots = polynomial->getRoots();
  if (roots.NaN) {
    this->ui->roots_label->setText("Polynomial has no integer roots");
  } else {
    std::stringstream rootsStream;
    std::string rootsOutput = "";
    rootsStream << "" << roots.minor << "," << roots.major << " \0";
    rootsStream >> rootsOutput;
    this->ui->roots_label->setText(QString::fromUtf8(rootsOutput.c_str()));
  }

  std::stringstream valueStream;
  std::string valueOutput = "";
  valueStream << polynomial->resolve(resolveBy);
  valueStream >> valueOutput;
  this->ui->value->setText(QString::fromUtf8(valueOutput.c_str()));

  this->ui->p_x->setText(QString::fromUtf8(polynomial->toString().c_str()));

  this->ui->canonical->setText(
      QString::fromUtf8(polynomial->toStringCanonical().c_str()));
}

void MainWindow::on_doubleSpinBox_valueChanged(double a) {
  polynomial->setA(a);
  MainWindow::updateUi();
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double b) {
  polynomial->setB(b);
  MainWindow::updateUi();
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double c) {
  polynomial->setC(c);
  MainWindow::updateUi();
}

void MainWindow::on_doubleSpinBox_4_valueChanged(double newX) {
  resolveBy = newX;
  MainWindow::updateUi();
}
