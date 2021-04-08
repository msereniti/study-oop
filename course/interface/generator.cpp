#include "generator.h"

TEventGenerator::TEventGenerator(int ms) : QTimer() {
  setTimerType(Qt::PreciseTimer);
  setInterval(ms);
}
