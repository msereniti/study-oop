#include "./application.h"
#include "./number.h"
#include <iostream>

int main() {
  Application *application = new Application();

  application->startInteractive();

  delete application;
}