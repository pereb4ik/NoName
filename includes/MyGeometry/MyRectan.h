#include "../MyMatrixes.h"

class Rectan{
public:
    Point mi, ma, a, b;
    bool loaded;
    Matrix *transformation;

    Rectan(){
        this->loaded = false;
    }

    void move(const Point &p){
        this->mi += p;
        this->ma += p;
        this->a += p;
        this->b += p;
    }

    Rectan(Point mi, Point ma, Matrix *transformation = new Matrix(get_move_matr())){
        this->loaded = false;
        this->mi = mi;
        this->ma = ma;
        this->b = Point(mi.x, ma.y);
        this->a = Point(ma.x, mi.y);
        this->transformation = transformation;
    }

    Point getmi(){
        return apply_transformation(mi, this->transformation);
    }

    Point getma(){
        return apply_transformation(ma, this->transformation);
    }

    Point geta(){
        return apply_transformation(a, this->transformation);
    }

    Point getb(){
        return apply_transformation(b, this->transformation);
    }

    void draw();
};