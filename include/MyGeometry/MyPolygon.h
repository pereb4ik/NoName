#ifndef _MYPOLYGON_H
#define _MYPOLYGON_H

#include "MyPoint.h"
#include "StandartIncludes.h"
#include "MyMatrixes.h"
#include "MyRectan.h"
#include "MyTriangle.h"
#include "StandartIncludes.h"

class MyPolygon{
public:
    vector < Point > verts;
    vector < Triangle > triangulation;
    Rectan *rct;
    Matrix *transformation;
    double area;

    MyPolygon(Matrix *transformation = new Matrix(get_ide_matr(3)));

    MyPolygon(const vector < Point > &verts, Matrix *transformation = new Matrix(get_ide_matr(3)));

    void update_bb();

    void triangulate();

    void add_vert(const Point &ver);

    void pop_back();

    int size() const;

    Point& operator [](int i);

    Point operator [](int i) const;

    Point get_val(int i) const;

    Point get(int i) const;

    void add_transform(const Matrix &m);

    float getArea();

    void draw_area(const Color &, const double & = 0, const Color & = Color());

    void draw_edges(const Color &);

    void loadFromFile(const string &s);
};

MyPolygon get_rectangle(double x, double y, double w, double h);

#endif