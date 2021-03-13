#include "fract.h"
#include "math.h"

Fract::Fract()
{

}

Fract::Fract(const int& fr_num)
{
    this->fr_num = fr_num;
    this->fr_den = 1;
}

Fract Fract::operator+ (const Fract& Fract)
{
    class Fract p;
    int int_NOK = SCM(Fract);
    int a = int_NOK/fr_den, b = int_NOK/Fract.fr_den;
    p.fr_num = fr_num*a + Fract.fr_num*b;
    p.fr_den = int_NOK;
    p.shorter();
    return p;
}

bool Fract::operator!= (const Fract& Fract)
{
    bool flag=false;
    int x1, x2;
    class Fract p;
    int int_NOK = SCM(Fract);
    int a = int_NOK/fr_den, b = int_NOK/Fract.fr_den;
    x1=int_NOK/this->fr_den;
    x2=int_NOK/Fract.fr_den;
    if (this->fr_num*x1==Fract.fr_num*x2)
    {
        flag = true;
    }
    return flag;
}

Fract Fract::operator* (const Fract& Fract)
{
    class Fract p;
    p.fr_num = fr_num*Fract.fr_num;
    p.fr_den = fr_den*Fract.fr_den;
    p.shorter();
    return p;
}

Fract Fract:: operator* (const int& value){
    Fract p;
    p.fr_num = fr_num*value;
    p.fr_den = fr_den;
    p.shorter();
    return p;
}


Fract Fract::operator/ (const Fract& Fract){
    class Fract p;

    if(Fract.fr_num<0){
        p.fr_num = -Fract.fr_den*fr_num;
        p.fr_den = Fract.fr_num*fr_den;
    }else{
        p.fr_num = Fract.fr_den*fr_num;
        p.fr_den = Fract.fr_num*fr_den;
    }
    p.shorter();
    return p;
}

Fract Fract::operator- (const Fract& Fract)
{
    class Fract p;
    int int_NOK = SCM(Fract);
    int a = int_NOK/fr_den;
    int b = int_NOK/Fract.fr_den;
    p.fr_num = fr_num*a - Fract.fr_num*b;
    p.fr_den = int_NOK;
    p.shorter();
    return p;
}

Fract Fract::operator- (){
    Fract p;
    p.fr_num = -fr_num;
    p.fr_den = fr_den;
    return p;
}

unsigned int Fract::SCM(const Fract& Fract)
{
    return (Fract.fr_den*fr_den)/GCD(Fract.fr_den,fr_den);
}

int Fract::GCD(const int& a1,const int& b1)
{
    int a = abs(a1), b = abs(b1);
    while(a!=0 && b!=0){
        if (a>=b)
            a = a%b;
        else
            b = b%a;
    }
    return a+b;
}


void Fract::shorter()
{
    int int_NOD = GCD(fr_num,fr_den);
    fr_num = fr_num/int_NOD;
    fr_den = fr_den/int_NOD;
}

Fract sqrt(Fract Fract){
    class Fract newValue;
    newValue.fr_num = sqrt(Fract.fr_num);
    newValue.fr_den = sqrt(Fract.fr_den);
    newValue.shorter();
    return newValue;
}

bool Fract::operator>= (const Fract& Fract)
{
    bool flag=false;
    int x1, x2;
    class Fract p;
    int int_NOK = SCM(Fract);
    int a = int_NOK/fr_den, b = int_NOK/Fract.fr_den;
    x1=int_NOK/this->fr_den;
    x2=int_NOK/Fract.fr_den;
    if (this->fr_num*x1>=Fract.fr_num*x2)
    {
        flag = true;
    }
    return flag;
}

bool Fract::operator > (int value){
    return this->fr_num > value*(int)this->fr_den;
}

bool Fract::operator < (int value){
    return this->fr_num < value*(int)this->fr_den;
}

bool Fract::operator == (int value){
    return this->fr_num == value*(int)this->fr_den;
}

bool Fract::operator == (Fract Fract)
{
    Fract.shorter();
    return (fr_den==Fract.fr_den && fr_num==Fract.fr_num);
}


ostream& operator << (ostream& os,const Fract& Fract)
{
    if(Fract.fr_num>=0 && Fract.fr_num % Fract.fr_den == 0){
        os<<Fract.fr_num/(int)Fract.fr_den;
    }else if(Fract.fr_num<0 && (-Fract.fr_num) % Fract.fr_den == 0){
        os<<Fract.fr_num/(int)Fract.fr_den;
    }else{
        Fract.fr_num<0?
                    os<<"-"<<"("<<-Fract.fr_num<<"/"<<Fract.fr_den<<")":
                    os<<"("<<Fract.fr_num<<"/"<<Fract.fr_den<<")";
    }
    return os;
}

istream& operator >> (istream& is,Fract& Fract)
{
    is>>Fract.fr_num>>Fract.fr_den;
    return is;
}