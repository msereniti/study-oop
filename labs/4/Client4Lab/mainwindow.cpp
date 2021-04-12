#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clientconnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ConnectionInfo info;

    info.bindAddres = QHostAddress("127.0.0.1");
    info.bindPort = 10000;
    info.sendAddres = QHostAddress("127.0.0.1");
    info.sendPort = 10001;

    _connection = new ClientConnection(this, info);

    connect(_connection, &ClientConnection::sigReceivedAnswer,
            this, &MainWindow::handlOnAnswerReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUi()
{
    //    PolynomialRoots roots = polynomial->getRoots();

    //    if (roots.NaN)
    //    {
    //        ui->roots_label->setText("Polynomial has no integer roots");
    //    }
    //    else
    //    {
    //        std::stringstream rootsStream;
    //        std::string rootsOutput = "";
    //        rootsStream << "" << roots.minor << "," << roots.major << " \0";
    //        rootsStream >> rootsOutput;

    //        ui->roots_label->setText(QString::fromUtf8(rootsOutput.c_str()));
    //    }

    //    std::stringstream valueStream;
    //    std::string valueOutput = "";
    //    valueStream << polynomial->resolve(resolveBy);
    //    valueStream >> valueOutput;

    //    ui->value->setText(QString::fromUtf8(valueOutput.c_str()));
    //    ui->p_x->setText(QString::fromUtf8(polynomial->toString().c_str()));
    //    ui->canonical->setText(QString::fromUtf8(polynomial->toStringCanonical().c_str()));
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

void MainWindow::on_sendToCalculation_clicked()
{
    Request req;

    req.aCoef = ui->coefA->value();
    req.bCoef = ui->coefB->value();
    req.cCoef = ui->coefC->value();
    req.xVarible = ui->varibleX->value();

    _connection->send(req);
}

void MainWindow::handlOnAnswerReceived(const QStringList &data)
{
    if(data.size() < 4)
        return;

    ui->roots_label->setText(data.at(0));
    ui->value->setText(data.at(1));
    ui->p_x->setText(data.at(2));
    ui->canonical->setText(data.at(3));
}
