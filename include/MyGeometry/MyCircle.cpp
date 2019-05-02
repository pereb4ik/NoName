#include "MyCircle.h"

Circle :: Circle(Matrix *m){
    this->transformation = m;
}

Circle :: Circle(const Point &p, const double &r, Matrix *m){
    this->transformation = m;
    this->p = p;
    this->r = r;
}

void Circle :: add_transform(const Matrix &m){
    *this->transformation *= m;
}

void Circle :: move(const Point &p){
    this->add_transform(get_move_matr(p));
}

void Circle :: hom(const double &x, const Point &p){
    this->add_transform(get_hom_matr(x, p));
    this->r *= x;
    this->r = abs(this->r);
}

Point Circle :: get_center() const {
    return apply_transformation(this->p, *transformation);
}