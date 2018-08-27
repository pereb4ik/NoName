#include "MyLine.h"

class Triangle{
public:
    Point *a, *b, *c;
    int inda, indb, indc;
    Point mi, ma;
    Matrix *transformation;

    Triangle() : a(), b(), c(){
        this->mi = Point(1e18, 1e18);
        this->ma = Point(-1e18, -1e18);
    }

    Triangle(Matrix *transformation, Point &a, Point &b, Point &c, int inda, int indb, int indc){
        this->transformation = transformation;
        this->a = &a;
        this->b = &b;
        this->c = &c;
        this->inda = inda;
        this->indb = indb;
        this->indc = indc;
        this->mi = Point(1e18, 1e18);
        this->ma = Point(-1e18, -1e18);
        this->mi.x = min(mi.x, a.x);
        this->mi.y = min(mi.y, a.y);
        this->ma.x = max(ma.x, a.x);
        this->ma.y = max(ma.y, a.y);
        this->mi.x = min(mi.x, b.x);
        this->mi.y = min(mi.y, b.y);
        this->ma.x = max(ma.x, b.x);
        this->ma.y = max(ma.y, b.y);
        this->mi.x = min(mi.x, c.x);
        this->mi.y = min(mi.y, c.y);
        this->ma.x = max(ma.x, c.x);
        this->ma.y = max(ma.y, c.y);
        if (eq(this->ma.x - this->mi.x, 0) || eq(this->ma.y - this->mi.y, 0)){
            exit(1);
        }
    }

    Point getmi(){
        return apply_transformation(this->mi, this->transformation);
    }

    Point geta(){
        return apply_transformation(*this->a, this->transformation);
    }

    Point getma(){
        return apply_transformation(this->ma, this->transformation);
    }

    Point getb(){
        return apply_transformation(*this->b, this->transformation);
    }

    Point getc(){
        return apply_transformation(*this->c, this->transformation);
    }

    void draw(const Color &);
};

//Shader *Triangle::sh = new Shader();

ostream& operator << (ostream &cout, Triangle p){
    cout << "a = " << p.a << "   ind = " << char(p.inda - 1 + 'a') << "\n";
    cout << "b = " << p.b << "   ind = " << char(p.indb - 1 + 'a') << "\n";
    cout << "c = " << p.c << "   ind = " << char(p.indc - 1 + 'a') << "\n";
    return cout;
}
