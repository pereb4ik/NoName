#ifndef _MYPOINT_H
#define _MYPOINT_H

#include "MyAngle.h"
#include "StandartIncludes.h"

class Point{
public:
    double x, y;

    Point();

    Point(const double &, const double &);

    Point(const double &, const double &, const double &, const double &);

    Point(const Point &, const Point &);

    pair < double, double > get_as_pair();

    friend bool operator == (const Point &, const Point &);

    friend bool operator != (const Point &, const Point &);

    friend bool operator < (const Point &, const Point &);

    friend bool operator > (const Point &, const Point &);

    friend bool operator <= (const Point &, const Point &);

    friend bool operator >= (const Point &, const Point &);

    friend Point operator / (const Point &, const double &);

    friend Point operator * (const Point &, const double &);

    double sqr_len() const;

    friend Point operator + (const Point &, const Point &);

    friend Point operator - (const Point &, const Point &);

    double len() const;

    Point get_normalized() const;

    Point ort();

    Point rot(const double &, const double &);

    Point rot(const Angle &);

    Point rot(const double &);

    friend double operator * (const Point &, const Point &);

    friend double operator % (const Point &, const Point &);
};

Angle angle_between_two_vectors(const Point &, const Point &);

Point &operator += (Point &, const Point &);

Point &operator -= (Point &, const Point &);

Point &operator /= (Point &, const Point &);

Point &operator *= (Point &, const Point &);

Point &operator *= (Point &, const double &);

Point &operator /= (Point &, const double &);

ostream& operator << (ostream &, const Point &);

Point operator - (const Point &p);

extern Point cur;
extern Point scrLB, scrx, scry;

Point getScrCenter();

#endif