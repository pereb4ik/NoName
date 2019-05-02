#ifndef _MYCIRCLE_H
#define _MYCIRCLE_H

#include "MyPoint.h"
#include "MyMatrixes.h"
#include "MyBaseOperations.h"

class Circle{
public:
    Point p;
    double r;
    Matrix *transformation;

    Circle(Matrix *m = new Matrix(get_ide_matr(3)));

    Circle(const Point &p, const double &r, Matrix *m = new Matrix(get_ide_matr(3)));

    void add_transform(const Matrix &m);

    void move(const Point &p);

    void hom(const double &x, const Point &p);

    Point get_center() const;
    
    void draw(const Color &);
};

#endif