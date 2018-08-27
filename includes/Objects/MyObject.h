#include "..\MyGeometry\MyGeometry.h"

class Object{
public:
    static Object origin;
    static vector < Object* > objs;
    static map < string, Object* > obj;
    string type, name;
    Point v;
    Object *parent;
    bool is_static, is_recalced, need_draw, on_ground;
    ComplexShape colision_mask;
    Matrix transformation, abs_transformation;

    virtual void draw(){

    }

    virtual void apply_force(const Point &f, const double &time){
        this->v += f * time;
    }

    virtual void apply_friction(const double &time){
        this->apply_force(Point(-this->v.x * 0.01, 0), time);
    }

    virtual void apply_acceleration(const double &time){
        this->apply_force(Point(0, -g), time);
    }

    virtual void collision(Object *obj){

    }

    virtual void every_frame(){

    }

    Object(const string &name = "", const string &type = ""){
        this->on_ground = false;
        this->name = name;
        this->type = type;
        obj[this->name] = this;
        this->need_draw = true;
        this->is_static = true;
        this->parent = &origin;
        this->is_recalced = false;
        objs.push_back(this);
        this->transformation = get_move_matr();
    }

    virtual void write_debug_information(){

    }

    virtual void recalc_abs_pos(){
        if (this == &origin){
            is_recalced = true;
            return;
        }
        if (this->is_recalced) return;
        this->is_recalced = true;
        parent->recalc_abs_pos();
        this->abs_transformation = parent->transformation * this->transformation;
    }

    Point get_abs_pos(){
        this->recalc_abs_pos();
        return Point(this->abs_transformation[2][0], this->abs_transformation[2][1]);
    }

    virtual void chenge_parent(Object *obj){
        obj->recalc_abs_pos();
        this->parent = obj;
        //this->pos = this->abs_pos - obj->abs_pos;
        //this->a = this->abs_a - obj->abs_a;
    }

    virtual void move(const Point &p){
        this->transformation *= get_move_matr(p);
        is_recalced = false;
    }

    virtual bool apply_speed(double time){
        this->move(v * time);
        return true;
    }
};

vector < Object* > Object::objs = vector< Object* >();
vector < Object* > *objs = &Object::objs;
map < string, Object* > Object::obj = map < string, Object* >();

Object *get_obj(const string &s){
    return Object::obj[s];
}

Object Object::origin = Object("origin", "origin");
Object Camera("Camera", "Camera"), *origin = &Object::origin;

Point to_gl_coords(const Point &p){
    //return Point((p.x - Camera.get_abs_pos().x) / WIDTH * 2 - 1, (p.y - Camera.get_abs_pos().y) / HEIGHT * 2 - 1);
    return Point((p.x - Camera.get_abs_pos().x), (p.y - Camera.get_abs_pos().y));
}
