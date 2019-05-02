#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "MyObject.h"
#include "MyPoint.h"
#include "DrawingFunctions.h"

class RisingTriangle : public Object{
public:
    Point now;

    RisingTriangle(const string &name);

    void draw();

    void every_frame();
};

class Cursor : public Object{
public:
    MyPolygon cursor;

    void draw();

    void every_frame();

    Cursor(const string &name);
};

class RotatingTriangle : public Object{
public:
    MyPolygon ss;
    Point ss_center, ss_rot_center;
    Angle asspeed, asrotspeed;
    double r;

    RotatingTriangle(const string &name);

    void draw();

    void every_frame();
};

class Arrow : public Object {
public:
    Point to, a, b;

    Arrow(const string &name);

    void draw();
};

class LoadedPolygon : public Object{
public:
    MyPolygon pol;

    LoadedPolygon(const string &name);

    void draw();
};

#endif