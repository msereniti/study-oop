
#ifndef POLINOM
#define POLINOM

#include "number.h"
#include <cmath>
#include <stdio.h>

struct PolynomialRoots {
  number major;
  number minor;
  bool NaN;
};

class Polinom {
private:
  number a;
  number b;
  number c;

public:
  void setA(number value) { this->a = value; };
  void setB(number value) { this->b = value; };
  void setC(number value) { this->c = value; };
  PolynomialRoots getRoots() {
    PolynomialRoots roots;

    number discriminant = std::pow(this->b, 2) - 4 * this->a * this->c;

    if (discriminant >= 0) {
      roots.major = (-this->b + std::sqrt(discriminant)) / (2 * this->a);
      roots.minor = (-this->b - std::sqrt(discriminant)) / (2 * this->a);
    }
    roots.NaN = discriminant < 0;

    return roots;
  }
  number resolve(number x) {
    return this->a + std::pow(x, 2) + this->b * x + this->c;
  }
  const char *toString() {
    char result[10000] = {'\0'};
    sprintf(result, "p(x) = %d*x^2 + %d*x + %d\n", this->a, this->b, this->c);
    return result;
  }
  const char *toStringCanonical() {
    PolynomialRoots roots = this->getRoots();
    if (roots.NaN) {
      return "real roots are not available\n";
    }
    char result[10000] = {'\0'};
    sprintf(result, "%d * (x - %d)(x - %d)\n", this->a, roots.major,
            roots.minor);
    return result;
  }

  Polinom() {
    this->a = 1;
    this->b = 1;
    this->c = 1;
  };
};

#endif