#include "MyRectan.h"

class Segment{
public:
    Point b, e;
    Matrix *transformation;

    Segment(Matrix *transformation = new Matrix(get_ide_matr(3))){
        ;
    }

    Segment(Point p, Matrix *transformation = new Matrix(get_ide_matr(3))){
        this->b = p;
        this->e = p;
    }

    Segment(Point b, Point e, Matrix *transformation = new Matrix(get_ide_matr(3))){
        this->b = b;
        this->e = e;
    }

    Point getb(){
        return apply_transformation(this->b, this->transformation);
    }

    Point gete(){
        return apply_transformation(this->e, this->transformation);
    }

    double len(){
        return Point(this->getb(), this->gete()).len();
    }

    double sqr_len(){
        return Point(this->getb(), this->gete()).sqr_len();
    }

    void draw(const Color&);
};