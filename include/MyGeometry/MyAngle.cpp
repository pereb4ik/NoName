#include "MyBaseOperations.h"
#include "StandartIncludes.h"
#include "MyAngle.h"

Angle :: Angle(){
    this->in_deg = 0;
    this->in_rad = 0;
}

Angle Angle :: set_as_deg(const double &x){
    this->in_deg = x;
    this->in_rad = x * PI / 180;
    this->normalize();
    return *this;
}

Angle Angle :: set_as_rad(const double &x){
    this->in_deg = x / PI * 180;
    this->in_rad = x;
    this->normalize();
    return *this;
}

void Angle :: normalize(){
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

double Angle :: get_as_deg() const{
    return this->in_deg;
}

double Angle :: get_as_rad() const{
    return this->in_rad;
}

Angle operator + (const Angle &a, const Angle &b){
    Angle ans;
    ans.set_as_rad(a.get_as_rad() + b.get_as_rad());
    ans.normalize();
    return ans;
}

Angle operator - (const Angle &a, const Angle &b){
    Angle ans;
    ans.set_as_rad(a.get_as_rad() - b.get_as_rad());
    ans.normalize();
    return ans;
}

Angle operator * (const Angle &a, const double &b){
    return Angle().set_as_rad(a.get_as_rad() * b);
}

Angle operator / (const Angle &a, const double &b){
    return Angle().set_as_rad(a.get_as_rad() / b);
}

Angle operator - (const Angle &a){
    return Angle().set_as_rad(-a.get_as_rad());
}

Angle scrTurnSpeed = Angle().set_as_deg(180);

