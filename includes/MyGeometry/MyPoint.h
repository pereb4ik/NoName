#include "MyAngle.h"

class Point{
public:
    double x, y;

    Point(){
        this->x = 0;
        this->y = 0;
    }

    Point(double x, double y){
        this->x = x;
        this->y = y;
    }

    Point(double x, double y, double xx, double yy){
        this->x = xx - x;
        this->y = yy - y;
    }

    Point(Point s, Point f){
        this->x = f.x - s.x;
        this->y = f.y - s.y;
    }

    pair < double, double > get_as_pair(){
        return make_pair(this->x, this->y);
    }

    friend bool operator == (Point f, Point s){
        return (eq(f.x, s.x) && eq(f.y, s.y));
    }

    friend bool operator != (Point f, Point s){
        return !(f == s);
    }

    friend bool operator < (Point f, Point s){
        if (ls(f.x, s.x)) return true;
        if (eq(f.x, s.x) && ls(f.y, s.y)) return true;
        return false;
    }

    friend bool operator > (Point f, Point s){
        return s < f && s != f;
    }

    friend bool operator <= (Point f, Point s){
        return f == s || f < s;
    }

    friend bool operator >= (Point f, Point s){
        return f == s || f > s;
    }

    friend Point operator / (Point p, double x){
        return Point(p.x / x, p.y / x);
    }

    friend Point operator * (Point p, double x){
        return Point(p.x * x, p.y * x);
    }

    inline double sqr_len(){
        return sqr(this->x) + sqr(this->y);
    }

    friend Point operator + (Point f, Point s){
        return Point(f.x + s.x, f.y + s.y);
    }

    friend Point operator - (Point f, Point s){
        return Point(f.x - s.x, f.y - s.y);
    }

    inline double len(){
        return sqrt(this->sqr_len());
    }

    Point get_normalized(){
        return (*this) / this->len();
    }

    Point ort(){
        return Point(-this->y, this->x);
    }

    Point rot(const double &ca, const double &sa){
        return *this * ca + this->ort() * sa;
    }

    Point rot(const Angle &ang){
        return this->rot(cos(ang.get_as_rad()), sin(ang.get_as_rad()));
    }

    Point rot(double ang){
        return this->rot(cos(ang), sin(ang));
    }

    friend double operator * (const Point &a, const Point &b){
        return a.x * b.y - a.y * b.x;
    }

    friend double operator % (const Point &a, const Point &b){
        return a.x * b.x + a.y * b.y;
    }

};

Angle angle_between_two_vectors(Point a, Point b){
    if (lseq(0, a * b)){
            return Angle().set_as_rad(
                acos(a % b / a.len() / b.len())
                );
        } else {
            return Angle().set_as_rad(
                -acos(a % b / a.len() / b.len())
                );
        }
    //return a / b;
}

Point &operator += (Point &a, Point b){
    return a = a + b;
}

Point &operator -= (Point &a, Point b){
    return a = a - b;
}

Point &operator *= (Point &a, double x){
    return a = a * x;
}

Point &operator /= (Point &a, double x){
    return a = a / x;
}

Point &operator /= (Point &a, const Point &b){
    if (eq(b.x, 0) || eq(b.y, 0)) {
        cout << "see MyGeometry   Point &operator /= (Point &a, const Point &b)\n";
        system("pause");
        exit(1);
    }
    return a = Point(a.x / b.x, a.y / b.y);
}

Point &operator *= (Point &a, const Point &b){
    if (eq(b.x, 0) || eq(b.y, 0)) {
        cout << "see MyGeometry   Point &operator *= (Point &a, const Point &b)\n";
        system("pause");
        exit(1);
    }
    return a = Point(a.x * b.x, a.y * b.y);
}

ostream& operator << (ostream &cout, Point p){
    cout << "(" << p.x << "; " << p.y << ")";
    return cout;
}