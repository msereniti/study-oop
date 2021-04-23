#ifndef POLINOM_H
#define POLINOM_H

#include <cmath>
#include <sstream>
#include <stdio.h>

#include "fract.h"

using namespace std;

template <typename number> struct PolynomialRoots {
  number major;
  number minor;
  bool NaN;
};

template <typename number> class Polinom {
private:
  number a;
  number b;
  number c;

public:
  Polinom() {
    this->a = 1;
    this->b = 1;
    this->c = 1;
  };

  void setA(number value) { this->a = value; };
  void setB(number value) { this->b = value; };
  void setC(number value) { this->c = value; };
  PolynomialRoots<number> getRoots() {
    PolynomialRoots<number> roots;
    roots.NaN = false;

    number discriminant = (this->b * this->b) - this->a * this->c * 4;

    if (discriminant >= 0) {
      roots.major = (-this->b + sqrt(discriminant)) / (this->a * 2);
      roots.minor = (-this->b - sqrt(discriminant)) / (this->a * 2);

      if (roots.major + roots.minor == -this->b * this->a &&
          roots.major * roots.minor == this->c / this->a) {
        roots.NaN = true;
      }
    }
    if (discriminant < 0) {
      roots.NaN = true;
    }

    return roots;
  }
  number resolve(number x) { return this->a + (x * x) + this->b * x + this->c; }
  std::string toString() {
    stringstream ss;
    ss << "p(x) =" << a << "*x^2 +" << b << "*x +" << c;
    return ss.str();
  }
  std::string toStringCanonical() {
    PolynomialRoots roots = this->getRoots();
    stringstream ss;
    if (roots.NaN) {
      ss << "real roots are not available";
    } else {
      ss << a << " * (" << roots.major << " - " << b << ")(" << roots.minor
         << " - " << c << ")";
    }
    return ss.str();
  }
};

#endif
