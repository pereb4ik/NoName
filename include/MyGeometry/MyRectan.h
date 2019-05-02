#ifndef _MYRECTAN_H
#define _MYRECTAN_H

#include "MyPoint.h"
#include "MyMatrixes.h"
#include "MyBaseOperations.h"

class Rectan{
public:
    Point *lb, *rt, *lt, *rb;
    Matrix *transformation;

    Rectan(Matrix *transformation = new Matrix(get_ide_matr(3)));

    void add_transfrom(const Matrix &m);

    Rectan(const Point &lb, const Point &rt, Matrix *transformation = new Matrix(get_ide_matr(3)));

    void update_rct(const Point &p);

    Point get_lb() const;

    Point get_rt() const;

    Point get_lt() const;

    Point get_rb() const;

    void draw(const Color &c) const;
};

#endif