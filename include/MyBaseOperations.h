#ifndef _MYBASEOPERTIONS_H
#define _MYBASEOPERTIONS_H

#include "StandartIncludes.h"

template < typename T >
T sqr(const T &x) {
    return x * x;
}

bool eq(const double &, const double &);

bool ls(const double &, const double &);

bool lseq(const double &, const double &);

int sign(const double &);

class Color{
public:
    double r, g, b, a;

    Color(const double &r, const double &g, const double &b, const double &a = 255);

    Color(const double &grey = 0, const double &a = 255);

    Color(const string &s);
};

class Complex{
public:
    double a, b;

    Complex(const double &a = 0, const double &b = 0);

    friend Complex operator + (const Complex &, const Complex &);

    friend Complex operator - (const Complex &, const Complex &);

    Complex operator -();

    friend Complex operator * (const Complex &, const Complex &);

    double get_sqrlen() const;

    friend Complex operator / (const Complex &, const Complex &);
};

template < class T >
T mypow(const T &, const long long &);

double count_speed_changing(const double &, const double &, const double &, const double &);

ostream& operator << (ostream &cout, const Color &c);

#endif