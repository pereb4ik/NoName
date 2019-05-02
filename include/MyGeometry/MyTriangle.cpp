#include "MyTriangle.h"

Triangle :: Triangle(Matrix *transformation){
    this->transformation = transformation;
    this->a = new Point();
    this->b = new Point();
    this->c = new Point();
}

void Triangle :: add_transform(const Matrix &m){
    *this->transformation *= m;
}

Triangle :: Triangle(Point *a, Point *b, Point *c, Matrix *transformation){
    this->transformation = transformation;
    this->a = a;
    this->b = b;
    this->c = c;
}

Triangle :: Triangle(const Point &a, const Point &b, const Point &c, Matrix *transformation){
    this->transformation = transformation;
    this->a = new Point(a);
    this->b = new Point(b);
    this->c = new Point(c);
}

Point Triangle :: get_a() const {
    return apply_transformation(*this->a, *this->transformation);
}

Point Triangle :: get_b() const {
    return apply_transformation(*this->b, *this->transformation);
}

Point Triangle :: get_c() const {
    return apply_transformation(*this->c, *this->transformation);
}

//Shader *Triangle::sh = new Shader();

ostream& operator << (ostream &cout, const Triangle &p){
    cout << "a = " << *p.a << "\n"; // "   ind = " << char(p.inda - 1 + 'a') << "\n";
    cout << "b = " << *p.b << "\n"; // "   ind = " << char(p.indb - 1 + 'a') << "\n";
    cout << "c = " << *p.c << "\n"; // "   ind = " << char(p.indc - 1 + 'a') << "\n";
    return cout;
}