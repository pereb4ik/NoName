#ifndef _MYANGLE_H
#define _MYANGLE_H

class Angle{
public:
    double in_deg, in_rad;
    Angle();

    Angle set_as_deg(const double &);

    Angle set_as_rad(const double &x);

    void normalize();

    double get_as_deg() const;

    double get_as_rad() const;

    friend Angle operator + (const Angle &, const Angle &);

    friend Angle operator - (const Angle &, const Angle &);

    friend Angle operator * (const Angle &, const double &);

    friend Angle operator / (const Angle &, const double &);
};

Angle operator - (const Angle &);

extern Angle scrTurnSpeed;

#endif