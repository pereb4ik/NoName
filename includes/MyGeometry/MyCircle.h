#include "MyTriangle.h"

class Circle{
public:
    Point p;
    double r;

    Circle(){}

    Circle(const Point &p, const double &r){
        this->p = p;
        this->r = r;
    }

    void move(const Point &p){
        this->p += p;
    }

    void draw(Color);
};
