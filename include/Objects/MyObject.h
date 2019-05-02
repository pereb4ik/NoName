#ifndef _MYOBJECT_H
#define _MYOBJECT_H

#include "StandartIncludes.h"

class Object{
public:
    static map < string, Object* > obj;
    string type, name;

    Object(const string &name, const string &type);

    virtual void draw();

    virtual void every_frame();
};

#endif