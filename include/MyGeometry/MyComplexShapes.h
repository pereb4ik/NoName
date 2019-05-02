#ifndef _MYCOMPLEXSHAPES_H
#define _MYCOMPLEXSHAPES_H

#include "StandartIncludes.h"
#include "MyPolygon.h"
#include "MyCircle.h"

class ComplexShape{
public:
    vector < MyPolygon > pols;
    vector < Circle > circles;
    Matrix *transformation;

    ComplexShape();

    void add(const MyPolygon &pl);

    void add(const Circle &crcl);

    void add_transform(const Matrix &m);
};

class ConvexPolygons{
public:
    vector < MyPolygon > pols;
    Matrix *transformation;

    void add(const MyPolygon &pl);

    void add_transform(const Matrix &m);

    MyPolygon& operator [](const int &i);

    MyPolygon operator [](const int &i) const;

    int size() const;

    friend ConvexPolygons operator + (const ConvexPolygons &a, const ConvexPolygons &b);

    void draw(const Color &);
};

#endif