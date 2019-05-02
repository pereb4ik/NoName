#ifndef _FLATANGLE_H
#define _FLATANGLE_H

#include "MyPoint.h"

// Always less than 180 degrees
class FlatAngle{
public:
    Point a, b, c;

    FlatAngle();

    FlatAngle(const Point &a, const Point &b, const Point &c);

    bool is_in(const Point &p) const ;
};

#endif