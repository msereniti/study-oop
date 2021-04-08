#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>

class TControlWindow : public QWidget
{
Q_OBJECT

    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;

public:
    TControlWindow(bool,QWidget *parent = 0);
    ~TControlWindow();

    inline void setEnable(const bool m) { setEnabled(m); }

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void switchMode();

signals:
    void closing();
    void reset();
    void step();
    void mode(bool);
};

#endif // CONTROLWINDOW_H
