#include "application.h"
#include <iostream>

void Application::startInteractive() {
  Polinom *polynomial = new Polinom();
  int userInput = -1;
  while (userInput != 5) {
    std::cout << "Available commands:\n\n";
    std::cout << "0: Setup polynomial\n";
    std::cout << "1: Get polynomial roots\n";
    std::cout << "2: Get polynomial value\n";
    std::cout << "3: Print polynomial in form p(x)\n";
    std::cout << "4: Print polynomial in canonical form\n";
    std::cout << "5: Exit\n\n";
    std::cout << "> ";
    std::cin >> userInput;

    if (userInput == 0) {
      number a = 1;
      std::cout << "Enter coefficient a\n> ";
      std::cin >> a;
      polynomial->setA(a);
      number b = 1;
      std::cout << "Enter coefficient b\n> ";
      std::cin >> b;
      polynomial->setB(b);
      number c = 1;
      std::cout << "Enter coefficient c\n> ";
      std::cin >> c;
      polynomial->setC(c);
      std::cout << "Success\n";
    } else if (userInput == 1) {
      PolynomialRoots roots = polynomial->getRoots();
      if (roots.NaN) {
        std::cout << "Polynomial has no integer roots\n";
      } else {
        std::cout << "Roots: " << roots.minor << ", " << roots.major << "\n";
      }
    } else if (userInput == 2) {
      number x = 0;
      std::cout << "Enter x value\n> ";
      std::cin >> x;
      std::cout << "Result: " << polynomial->resolve(x) << "\n";
    } else if (userInput == 3) {
      std::cout << "\n";
      std::cout << polynomial->toString() << "\n";
      std::cout << "\n";
    } else if (userInput == 4) {
      std::cout << "\n";
      std::cout << polynomial->toStringCanonical() << "\n";
      std::cout << "\n";
    }
    std::cout << "\n";
  }
  delete polynomial;
}
