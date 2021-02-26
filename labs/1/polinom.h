
#ifndef POLINOM
#define POLINOM

#include "number.h"

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
  void setA(number value);
  void setB(number value);
  void setC(number value);
  PolynomialRoots getRoots();
  number resolve(number x);
  const char *toString();
  const char *toStringCanonical();

  Polinom();
};

#include "polinom.cpp"

#endif