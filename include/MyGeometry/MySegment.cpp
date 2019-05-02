#include "MySegment.h"

Segment :: Segment(Matrix *transformation){
    this->transformation = transformation;
}

Segment :: Segment(const Point &p, Matrix *transformation){
    this->b = p;
    this->e = p;
    this->transformation = transformation;
}

Segment :: Segment(const Point &b, const Point &e, Matrix *transformation){
    this->b = b;
    this->e = e;
    this->transformation = transformation;
}

Point Segment :: getb() const {
    return apply_transformation(this->b, *this->transformation);
}

Point Segment :: gete() const {
    return apply_transformation(this->e, *this->transformation);
}

double Segment :: len() const {
    return Point(this->getb(), this->gete()).len();
}

double Segment :: sqr_len(){
    return Point(this->getb(), this->gete()).sqr_len();
}

void Segment :: add_transform(const Matrix &m){
    *this->transformation *= m;
}