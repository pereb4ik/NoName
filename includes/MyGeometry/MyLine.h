#include "MySegment.h"

class Line{
public:
    Point p, v;

    Line(){}

    Line(Point a, Point b){
        this->p = a;
        this->v = a - b;
    }

    Line(Segment s){
        *this = Line(s.b, s.e);
    }

    friend bool operator || (Line a, Line b){
        return eq(0, a.v * b.v);
    }

    friend bool operator == (Line a, Line b){
        return eq(0, a.v * (b.p - a.p)) && (a || b);
    }

    Point proj(Point a){
        return this->v.get_normalized()
                * cos(
                    angle_between_two_vectors(this->v, a - this->p).get_as_rad()
                )
                * (a - this->p).len()   
                + this->p;
    }

    double dist(Point a){
        return (a - this->proj(a)).len();
    }

    bool is_in_one_half_plane(Point a, Point b){
        if (eq(Point(this->p, a) * this->v, 0) || eq(this->v * Point(this->p, b), 0)) return true;
        return sign(Point(this->p, a) * this->v) != sign(this->v * Point(this->p, b));
    }
};