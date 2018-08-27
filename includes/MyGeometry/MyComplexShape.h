#include "MyPolygon.h"

class ComplexShape{
public:
    vector < MyPolygon > pols;
    vector < Circle > circles;

    void add(MyPolygon pl){
        pols.push_back(pl);
    }

    void add(Circle crcl){
        circles.push_back(crcl);
    }

    void move(const Point &p){
        for (int i = 0; i < pols.size(); i++){
            pols[i].move(p);
        }
        for (int i = 0; i < circles.size(); i++){
            circles[i].move(p);
        }
    }
};
