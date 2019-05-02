//#include "MyAngle.h"

#include "MyBaseOperations.h"
#include "MyPoint.h"

Point :: Point(){
    this->x = 0;
    this->y = 0;
}

Point :: Point(const double &x, const double &y){
    this->x = x;
    this->y = y;
}

Point :: Point(const double &x, const double &y, const double &xx, const double &yy){
    this->x = xx - x;
    this->y = yy - y;
}

Point :: Point(const Point &s, const Point &f){
    this->x = f.x - s.x;
    this->y = f.y - s.y;
}

pair < double, double > Point :: get_as_pair(){
    return make_pair(this->x, this->y);
}

bool operator == (const Point &f, const Point &s){
    return (eq(f.x, s.x) && eq(f.y, s.y));
}

bool operator != (const Point &f, const Point &s){
    return !(f == s);
}

bool operator < (const Point &f, const Point &s){
    if (ls(f.x, s.x)) return true;
    if (eq(f.x, s.x) && ls(f.y, s.y)) return true;
    return false;
}

bool operator > (const Point &f, const Point &s){
    return s < f && s != f;
}

bool operator <= (const Point &f, const Point &s){
    return f == s || f < s;
}

bool operator >= (const Point &f, const Point &s){
    return f == s || f > s;
}

Point operator / (const Point &p, const double &x){
    return Point(p.x / x, p.y / x);
}

Point operator * (const Point &p, const double &x){
    return Point(p.x * x, p.y * x);
}

double Point :: sqr_len() const {
    return sqr(this->x) + sqr(this->y); // не норм
}

Point operator + (const Point &f, const Point &s){
    return Point(f.x + s.x, f.y + s.y);
}

Point operator - (const Point &f, const Point &s){
    return Point(f.x - s.x, f.y - s.y);
}

double Point :: len() const {
    return sqrt(this->sqr_len());
}

Point Point :: get_normalized() const {
    return (*this) / this->len();
}

Point Point :: ort(){
    return Point(-this->y, this->x);
}

Point Point :: rot(const double &ca, const double &sa){
    return *this * ca + this->ort() * sa;
}

Point Point :: rot(const Angle &ang){
    return this->rot(cos(ang.get_as_rad()), sin(ang.get_as_rad()));
}

Point Point :: rot(const double &ang){
    return this->rot(cos(ang), sin(ang));
}

double operator * (const Point &a, const Point &b){
    return a.x * b.y - a.y * b.x;
}

double operator % (const Point &a, const Point &b){
    return a.x * b.x + a.y * b.y;
}

Angle angle_between_two_vectors(const Point &a, const Point &b){
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

Point &operator += (Point &a, const Point & b){
    return a = a + b;
}

Point &operator -= (Point &a, const Point &b){
    return a = a - b;
}

Point &operator *= (Point &a, const double &x){
    return a = a * x;
}

Point &operator /= (Point &a, const double &x){
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

ostream& operator << (ostream &cout, const Point &p){
    cout << "(" << p.x << "; " << p.y << ")";
    return cout;
}

Point operator - (const Point &p){
    return Point(0, 0) - p;
}

Point cur(WIDTH / 2, HEIGHT / 2);
Point scrLB(0, 0), scrx(1, 0), scry(0, 1);

Point getScrCenter(){
    return scrLB + (scrx * WIDTH + scry * HEIGHT) / 2;
}