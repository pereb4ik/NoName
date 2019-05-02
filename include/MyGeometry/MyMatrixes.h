#ifndef _MYMATRIXES_H
#define _MYMATRIXES_H

#include "StandartIncludes.h"
#include "MyPoint.h"


class Matrix{
public:
    vector < vector < double > > matr;
    int n, m;

    Matrix ();

    Matrix (const vector < vector < double > > &mtr);

    Matrix (const vector < double > &mtr);

    Matrix (const Point &p);

    vector < double > &operator [](const int &i);

    vector < double > operator [](const int &i) const;

    Point get_as_point();

    vector < double > get_as_vector();    
};

Matrix operator * (const Matrix &m1, const Matrix &m2);

Matrix &operator *= (Matrix &a, const Matrix &b);

Matrix get_ide_matr(const int &n);

Matrix get_move_matr(const Point &p = Point());

Matrix get_rot_matr(const double &x, const Point &p = Point());

Matrix get_rot_matr(const Point &p, const double &x);

Matrix get_rot_matr(const Angle &x, const Point &p = Point());

Matrix get_rot_matr(const Point &p, const Angle &x);

Matrix get_hom_matr(const double &x, const Point &p = Point());

Matrix get_hom_matr(const Point &p, const double &x);

Point apply_transformation(const Point &p, const Matrix &m);

extern Matrix CameraTransform;

#endif