#include "MyObject.h"

    map < string, Object* > Object::obj = *new map < string, Object* >();

    Object :: Object(const string &name, const string &type){
        this->name = name;
        this->type = type;
        obj[this->name] = this;
    }
    
    void Object :: draw(){}

    void Object :: every_frame(){}