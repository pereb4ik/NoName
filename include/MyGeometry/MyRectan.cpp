#include "MyRectan.h"

Rectan :: Rectan(Matrix *transformation){
    this->lb = new Point();
    this->rt = new Point();
    this->lt = new Point();
    this->rb = new Point();
    this->transformation = transformation;
}

void Rectan :: add_transfrom(const Matrix &m){
    *this->transformation *= m;
}

Rectan :: Rectan(const Point &lb, const Point &rt, Matrix *transformation){
    this->lb = new Point(lb);
    this->rt = new Point(rt);
    this->lt = new Point(this->lb->x, this->rt->y);
    this->rb = new Point(this->rt->x, this->lb->y);
    this->transformation = transformation;
}

void Rectan :: update_rct(const Point &p){
    *this = Rectan( Point(min(p.x, this->lb->x), min(p.y, this->lb->y)), 
                    Point(max(p.x, this->rt->x), max(p.y, this->rt->y)), 
                    this->transformation
                  );
}

Point Rectan :: get_lb() const {
    return apply_transformation(*this->lb, *this->transformation);
}

Point Rectan :: get_rt() const {
    return apply_transformation(*this->rt, *this->transformation);
}

Point Rectan :: get_lt() const {
    return apply_transformation(*this->lt, *this->transformation);
}

Point Rectan :: get_rb() const {
    return apply_transformation(*this->rb, *this->transformation);
}