#include "MyLine.h"

    Line :: Line(){}

    Line :: Line(Point a, Point b){
        this->p = a;
        this->v = a - b;
    }

    Line :: Line(Segment s){
        *this = Line(s.getb(), s.gete());
    }

    bool operator || (Line a, Line b){
        return eq(0, a.v * b.v);
    }

    bool operator == (Line a, Line b){
        return eq(0, a.v * (b.p - a.p)) && (a || b);
    }

    Point Line :: proj(Point a) const {
        return this->v.get_normalized()
                * cos(
                    angle_between_two_vectors(this->v, a - this->p).get_as_rad()
                )
                * (a - this->p).len()   
                + this->p;
    }

    double Line :: dist(Point a) const {
        return (a - this->proj(a)).len();
    }

    bool Line :: is_on_line(const Point &p) const {
        return eq(0, Point(this->p, p) * v);
    }

    /// return values : IN_DIFFERENT_HALF_PLANE; IN_SAME_HALF_PLANE; FIRST_ON_LINE; SECOND_ON_LINE; BOTH_ON_LINE
    int Line :: is_in_one_half_plane(const Point &a, const Point &b) const {
        if (this->is_on_line(a) && this->is_on_line(b)) return BOTH_ON_LINE | FIRST_ON_LINE | SECOND_ON_LINE;
        if (this->is_on_line(a)) return FIRST_ON_LINE;
        if (this->is_on_line(b)) return SECOND_ON_LINE;
        //if (eq(Point(this->p, a) * this->v, 0) || eq(this->v * Point(this->p, b), 0)) return true;
        Point tmp = this->p + this->v;
        return (sign(Point(a, this->p) * Point(a, tmp)) == sign(Point(b, this->p) * Point(b, tmp))) ? IN_SAME_HALF_PLANE : IN_DIFFERENT_HALF_PLANE;
        //return (sign(Point(this->p, a) * this->v) != sign(this->v * Point(this->p, b))) ? IN_SAME_HALF_PLANE : IN_DIFFERENT_HALF_PLANE;
    }

    Color Line :: get_abc() const {
        Color ans;
        ans.r = v.y;
        ans.g = -v.x;
        ans.b = -(ans.r * p.x + ans.g * p.y);
        return ans;
    }

    double Line :: get_directional_dist(const Point &a) const {
        Color c = get_abc();
        return (c.r * a.x + c.g * a.y + c.b) / sqrt(sqr(c.r) + sqr(c.g));
    }

    // Ray

    Ray :: Ray(){}

    Ray :: Ray(const Point &from, const Point &to){
        this->b = from;
        this->v = to - from;
    }

    bool Ray :: is_on_ray(const Point &a) const {
        return eq((a - this->b) * this->v, 0) && ls(0, (a - this->b) % this->v);
    }