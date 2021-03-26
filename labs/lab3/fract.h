#ifndef FRACT_H
#define FRACT_H

#include <iostream>
using namespace std;

class Fract {
  int fr_num;
  unsigned int fr_den;
  unsigned int SCM(const Fract &);
  int GCD(const int &, const int &);
  void shorter();

public:
  Fract();
  Fract(const int &);
  Fract operator+(const Fract &);
  Fract operator-(const Fract &);
  Fract operator-();
  Fract operator*(const Fract &);
  Fract operator*(const int &);
  Fract operator/(const Fract &);
  bool operator>=(const Fract &);
  bool operator!=(const Fract &);
  bool operator>(int);
  bool operator<(int);
  bool operator==(int);
  bool operator==(Fract);
  friend Fract sqrt(Fract);
  friend ostream &operator<<(ostream &os, const Fract &);
  friend istream &operator>>(istream &is, Fract &);
};

#endif // FRACT_H
