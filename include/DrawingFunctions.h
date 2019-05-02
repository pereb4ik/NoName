#ifndef _DRAWINGFUNCTIONS_H
#define _DRAWINGFUNCTIONS_H

#include "MyBaseOperations.h"
#include "StandartIncludes.h"
/*#include "MyPoint.h"
#include "MySegment.h"
#include "MyTriangle.h"
#include "MyPolygon.h"
#include "MyCircle.h"*/
#include "MyGeometry.h"

void add_gl_point(const Point &a);

void add_gl_color(const Color &c = Color());

void draw_triangle(const Point &a, const Point &b, const Point &c, const Color &fillColor = Color());

void add_normal_gl_point(const Point &p);

extern vector < pair < Segment, Color > > globalDrawingSegmentVector;

void add_to_draw(const Segment &s, const Color &c);

void drawSegments(const Point &pOV);

#endif