//#include "../OpenGLEventsHandler.h"
//#include "../includes.h"

#include "StandartIncludes.h"
#include "MyBaseOperations.h"

bool eq(const double &a, const double &b){
    return fabs(a - b) < EPS;
}

bool ls(const double &a, const double &b){
    return a < b && !eq(a, b);
}

bool lseq(const double &a, const double &b){
    return a < b || eq(a, b);
}

int sign(const double &x){
    if (eq(x, 0)) return 0;
    return ls(0, x) * 2 - 1;
}

long long hextodec(string s){
    long long ans = 0;
    for (int i = 0; i < s.size(); i++){
        if ('A' <= s[i] && s[i] <= 'F'){
            ans = ans * 16 + 10 + s[i] - 'A';
        }
        if ('a' <= s[i] && s[i] <= 'f'){
            ans = ans * 16 + 10 + s[i] - 'a';
        }
        if ('0' <= s[i] && s[i] <= '9'){
            ans = ans * 16 + s[i] - '0';
        }
    }
    return ans;
}

Color::Color(const double &r, const double &g, const double &b, const double &a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(const double &grey, const double &a){
    this->r = this->g = this->b = grey;
    this->a = a;
}

Color::Color(const string &s){
    long long tmp = hextodec(s);
    this->b = tmp / 1 % 256;
    this->g = tmp / 256 % 256;
    this->r = tmp / (256 * 256) % 256;
}

Complex::Complex(const double &a, const double &b){
    this->a = a;
    this->b = b;
}

Complex operator + (const Complex &x, const Complex &y){
    return Complex(x.a + y.a, x.b + y.b);
}

Complex operator - (const Complex &x, const Complex &y){
    return Complex(x.a - y.a, x.b - y.b);
}

Complex Complex::operator -(){
    return Complex() - *this;
}

Complex operator * (const Complex &x, const Complex &y){
    return Complex(x.a * y.a - x.b * y.b, x.a * y.b + x.b * y.a);
}

double Complex::get_sqrlen() const {
    return sqr(this->a) + sqr(this->b); // норм   для дабов  
}

Complex operator / (const Complex &x, const Complex &y){
    return x * Complex(y.a / y.get_sqrlen(), -y.b / y.get_sqrlen());
}

template < class T >
T mypow(const T &x, const long long &pw){
    if (pw == 0) return x / x;
    if (pw % 2 == 0){
        return sqr(mypow(x, pw / 2));
    } else {
        return x * mypow(x, pw - 1);
    }
}

double count_speed_changing(const double &v, const double &d, const double &c, const double &delta_time){
    Complex t1 = Complex(1) - sqr(Complex(EPS)) * Complex(c) / Complex(2) - Complex(0, sqrt(fabs(sqr(EPS) * c * (2 - sqr(EPS) * c)))) / Complex(2);
    Complex t2 = Complex(1) - sqr(Complex(EPS)) * Complex(c) / Complex(2) + Complex(0, sqrt(fabs(sqr(EPS) * c * (2 - sqr(EPS) * c)))) / Complex(2);
    Complex a0 = v;
    Complex a1 = v - (v * EPS + d) * EPS * c;
    Complex alpha2 = (a0 * t1 + a1) / (t1 + t2);
    Complex alpha1 = a0 - alpha2;
    // Complex an = alpha1 * mypow(t1, n) + alpha2 * mypow(t2, n);
    Complex an = alpha1 * mypow(t1, (long long)(delta_time / EPS)) + alpha2 * mypow(t2, (long long)(delta_time / EPS));
    if (!eq(an.b, 0)){
        cout << "ERROR see : 'double count_speed_changing' in MyBaseOperations.h\n";
        system("pause");
        exit(1);
    }
    return an.a;
}

ostream& operator << (ostream &cout, const Color &p){
    cout << "< " << p.r << "; " << p.g << "; " << p.b << " >";
    return cout;
}