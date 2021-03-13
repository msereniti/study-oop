#include "number.h"
#include <math.h>
#include <stdio.h>

#include "polinom.h"

using namespace std;

Polinom::Polinom() {
  this->a = 1;
  this->b = 1;
  this->c = 1;
};

void Polinom::setA(number value) { this->a = value; };
void Polinom::setB(number value) { this->b = value; };
void Polinom::setC(number value) { this->c = value; };
PolynomialRoots Polinom::getRoots() {
  PolynomialRoots roots;
  roots.NaN = false;

  number discriminant = (this->b * this->b)  - this->a * this->c * 4;
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
number Polinom::resolve(number x) {
  return this->a + (x * x) + this->b * x + this->c;
}
const char *Polinom::toString() {
  char result[10000] = {'\0'};
  cout<<"p(x) ="<<a<<"*x^2 +"<<b<<"*x +"<<c;
  return result;
}
const char *Polinom::toStringCanonical() {
  PolynomialRoots roots = this->getRoots();
  if (roots.NaN) {
    return "real roots are not available\n";
  }
  char result[10000] = {'\0'};
  cout<<a<<" * (x - "<<b<<")(x - "<<c<<")"<<endl;
  return result;
}