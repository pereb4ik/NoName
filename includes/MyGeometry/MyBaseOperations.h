#include "../OpenGLEventsHandler.h";

template < typename T >
T sqr(const T &x){
    return x * x;
}

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

class Color{
public:
    float r, g, b, a;

    Color(const float &r, const float &g, const float &b, const float &a = 255){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color(const float &grey = 0, const float &a = 255){
        this->r = this->g = this->b = grey;
        this->a = a;
    }
};