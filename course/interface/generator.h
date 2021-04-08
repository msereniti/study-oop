#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QTimer>

class TEventGenerator : public QTimer {
  Q_OBJECT
public:
  TEventGenerator(int = 1000);
};

#endif // GENERATOR_H
