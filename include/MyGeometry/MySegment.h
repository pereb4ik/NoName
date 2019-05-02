#ifndef _MYSEGMENT_H
#define _MYSEGMENT_H

#include "MyPoint.h"
#include "MyMatrixes.h"
#include "MyBaseOperations.h"

class Segment{
public:
    Point b, e;
    Matrix *transformation;

    Segment(Matrix *transformation = new Matrix(get_ide_matr(3)));

    Segment(const Point &p, Matrix *transformation = new Matrix(get_ide_matr(3)));

    Segment(const Point &b, const Point &e, Matrix *transformation = new Matrix(get_ide_matr(3)));

    Point getb() const;

    Point gete() const;

    double len() const;

    double sqr_len();

    void add_transform(const Matrix &m);

    void draw(const Color&);

    double dist_to(const Point &p);
};

#endif