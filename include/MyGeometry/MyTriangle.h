#ifndef _MYTRIANGLE_H
#define _MYTRIANGLE_H

#include "MyPoint.h"
#include "MyMatrixes.h"
#include "MyBaseOperations.h"

class Triangle{
public:
    Point *a, *b, *c;
    Matrix *transformation;

    Triangle(Matrix *transformation = new Matrix(get_ide_matr(3)));

    void add_transform(const Matrix &m);

    Triangle(Point *a = new Point(), Point *b = new Point(), Point *c = new Point(), Matrix *transformation = new Matrix(get_ide_matr(3)));

    Triangle(const Point &a, const Point &b, const Point &c, Matrix *transformation = new Matrix(get_ide_matr(3)));

    Point get_a() const;

    Point get_b() const;

    Point get_c() const;

    void draw(const Color &);
};

ostream& operator << (ostream &cout, const Triangle &p);

#endif