#ifndef _MYGEOMETRY_H
#define _MYGEOMETRY_H

#include "MyPolygon.h"
#include "MyMatrixes.h"
#include "MyPoint.h"
#include "MyLine.h"
#include "MySegment.h"
#include "MyTriangle.h"
#include "MyRectan.h"
#include "MyCircle.h"
#include "MyComplexShapes.h"
#include "MyFlatAngle.h"

// for segment-line intersection
#define SEGMENT_DOESNT_INTERSECT_LINE 0
#define SEGMENT_INTERSECT_LINE 1
#define BEGIN_LIES_ON_LINE 2
#define END_LIES_ON_LINE 4
#define SEGMENT_LIES_ON_LINE 8
// for segment-line intersection



// for segment-segment intersection
#define SEGMENTS_DOESNT_INTERSECT 0
#define SEGMENTS_INTERSECTS 1
#define FIRST_END_OF_FIRST_LIES_ON_SECOND 2
#define SECOND_END_OF_FIRST_LIES_ON_SECOND 4
#define FIRST_END_OF_SECOND_LIES_ON_FIRST 8
#define SECOND_END_OF_SECOND_LIES_ON_FIRST 16
#define FIRST_LIES_ON_SECOND 32
#define SECOND_LIES_ON_FIRST 64
#define SEGMENTS_ARE_EQUAL 128
// for segment-segment intersection

bool is_on_segment(const Point &p, const Segment &s);

bool is_intersects(const Circle &c, const Line &l);

bool is_intersects(const Segment &s, const Circle &c);

bool is_intersects(const Circle &c1, const Circle &c2);

bool is_intersects(const Line &f, const Line &s);

int intersection_type(const Segment &s, const Line &l); // O(1)

bool is_intersects(const Segment &s, const Line &l);

int intersection_type(const Segment &a, const Segment &b);

bool is_intersects(const Segment &f, const Segment &s); // O(1) touching by ends of segments will return false

bool is_in(const Point &p, const Rectan &r);

bool is_in(const Segment &s, const Rectan &r);

bool is_in(const MyPolygon &p, const Rectan &r);

template < class T >
bool is_in(const T &a, const Rectan &r){
    cout << "ekarni bobai zhmi\n";
    return true;
}

template < class T >
bool is_intersects(const T &r2, const Rectan &r1){
    if (is_intersects(Segment(r1.get_lb(), r1.get_lt()), r2)) return true;
    if (is_intersects(Segment(r1.get_lt(),  r1.get_rt()), r2)) return true;
    if (is_intersects(Segment(r1.get_rt(), r1.get_rb()), r2)) return true;
    if (is_intersects(Segment(r1.get_rb(),  r1.get_lb()), r2)) return true;
    return is_in(r2, r1);
}

bool is_intersects(const Rectan &r1, const Rectan &r2);

bool intersect_checker_like_segment(const Segment &a, const Segment &b);

bool intersect_checker_like_interval(const Segment &a, const Segment &b);

bool is_intersects(const Segment &s, const MyPolygon &p, bool (*intersect_checker)(const Segment &, const Segment &) = &intersect_checker_like_interval);

template < class T >
bool is_intersects(const T &x, const MyPolygon &pol){
    if (!is_intersects(x, *pol.rct)) return false;
    for (int i = 0; i < pol.size(); i++){
        if (is_intersects(Segment(pol.get(i), pol.get(i + 1)), x)) return true;
    }
    return false;
}

bool is_intersects(const MyPolygon &x, const MyPolygon &pol);

bool is_intersects(const ComplexShape &cs1, const ComplexShape &cs2);

bool is_in(const Point &p, const MyPolygon &pol);

bool in_good_order(const Point &a, const Point &b, const Point &c);

vector < int > max_convex_underpolygon(const MyPolygon &p);

ConvexPolygons PolygonDecomposition(const MyPolygon &p);

Point get_intersection(const Line &f, const Line &s);

Point get_intersection(const Line &l, const Segment &s);

Point get_intersection(const Ray &r, const Segment &s);

bool is_intersects(const Ray &r, const Segment &s);

#endif