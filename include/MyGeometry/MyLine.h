#ifndef _MYLINE_H
#define _MYLINE_H

#define IN_DIFFERENT_HALF_PLANE 1
#define IN_SAME_HALF_PLANE 2
#define FIRST_ON_LINE 4
#define SECOND_ON_LINE 8
#define BOTH_ON_LINE 16

#include "MyPoint.h"
#include "MyBaseOperations.h"
#include "MySegment.h"

class Line{
public:
    Point p, v;

    Line();

    Line(Point a, Point b);

    Line(Segment s);

    friend bool operator || (Line a, Line b);

    friend bool operator == (Line a, Line b);

    Point proj(Point a) const;

    double dist(Point a) const;

    bool is_on_line(const Point &p) const;

    int is_in_one_half_plane(const Point &a, const Point &b) const;

    Color get_abc() const ;

    double get_directional_dist(const Point &a) const;
};

class Ray{
public:
    Point b, v;

    Ray();

    Ray(const Point &from, const Point &to);

    bool is_on_ray(const Point &p) const ;
};

#endif