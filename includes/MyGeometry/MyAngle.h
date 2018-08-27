#include "MyBaseOperations.h"

class Angle{
public:
    double in_deg, in_rad;
    Angle(){
        this->in_deg = 0;
        this->in_rad = 0;
    }

    Angle set_as_deg(double x){
        this->in_deg = x;
        this->in_rad = x * PI / 180;
        this->normalize();
        return *this;
    }

    Angle set_as_rad(double x){
        this->in_deg = x / PI * 180;
        this->in_rad = x;
        this->normalize();
        return *this;
    }

    void normalize(){
        while (this->in_deg < 0){
            this->in_deg += 360;
        }
        while (this->in_deg > 360){
            this->in_deg -= 360;
        }
        while (this->in_rad < 0){
            this->in_rad += 2 * PI;
        }
        while (this->in_rad > 2 * PI){
            this->in_rad -= 2 * PI;
        }
    }

    double get_as_deg() const{
        return this->in_deg;
    }

    double get_as_rad() const{
        return this->in_rad;
    }

    friend Angle operator + (Angle a, Angle b){
        Angle ans;
        ans.set_as_rad(a.get_as_rad() + b.get_as_rad());
        ans.normalize();
        return ans;
    }

    friend Angle operator - (Angle a, Angle b){
        Angle ans;
        ans.set_as_rad(a.get_as_rad() - b.get_as_rad());
        ans.normalize();
        return ans;
    }
};

Angle operator - (Angle a){
    return Angle().set_as_rad(-a.get_as_rad());
}