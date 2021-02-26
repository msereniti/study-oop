#include "number.h"
#include <cmath>
#include <stdio.h>

#include "polinom.h"

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

  number discriminant = std::pow(this->b, 2) - 4 * this->a * this->c;

  if (discriminant >= 0) {
    roots.major = (-this->b + std::sqrt(discriminant)) / (2 * this->a);
    roots.minor = (-this->b - std::sqrt(discriminant)) / (2 * this->a);
  }
  roots.NaN = discriminant < 0;

  return roots;
}
number Polinom::resolve(number x) {
  return this->a + std::pow(x, 2) + this->b * x + this->c;
}
const char *Polinom::toString() {
  char result[10000] = {'\0'};
  sprintf(result, "p(x) = %d*x^2 + %d*x + %d\n", this->a, this->b, this->c);
  return result;
}
const char *Polinom::toStringCanonical() {
  PolynomialRoots roots = this->getRoots();
  if (roots.NaN) {
    return "real roots are not available\n";
  }
  char result[10000] = {'\0'};
  sprintf(result, "%d * (x - %d)(x - %d)\n", this->a, roots.major, roots.minor);
  return result;
}
