#include "MyFlatAngle.h"

FlatAngle :: FlatAngle(){}

FlatAngle :: FlatAngle(const Point &a, const Point &b, const Point &c){
    this->a = a;
    this->b = b;
    this->c = c;
}