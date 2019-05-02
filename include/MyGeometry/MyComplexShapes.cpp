#include "MyComplexShapes.h"

    ComplexShape :: ComplexShape(){}

    void ComplexShape :: add(const MyPolygon &pl){
        pols.push_back(pl);
    }

    void ComplexShape :: add(const Circle &crcl){
        circles.push_back(crcl);
    }

    void ComplexShape :: add_transform(const Matrix &m){
        *this->transformation *= m;
    }

    // ConvexPolygons

    void ConvexPolygons :: add(const MyPolygon &pl){
        pols.push_back(pl);
    }

    void ConvexPolygons :: add_transform(const Matrix &m){
        *this->transformation *= m;
    }

    MyPolygon& ConvexPolygons :: operator [](const int &i){
        return this->pols[i];
    }

    MyPolygon ConvexPolygons :: operator [](const int &i) const{
        return this->pols[i];
    }

    int ConvexPolygons :: size() const {
        return this->pols.size();
    }

    ConvexPolygons operator + (const ConvexPolygons &a, const ConvexPolygons &b){
        ConvexPolygons ans;
        if (a.size() > b.size()){
            ans = a;
            for (int i = 0; i < b.size(); i++){
                ans.add(b[i]);
            }
        } else {
            ans = b;
            for (int i = 0; i < a.size(); i++){
                ans.add(a[i]);
            }
        }
        return ans;
    }