#include "../DrawingFunctions.h"

class Player : public Object {
public:
    MyPolygon main_char;

    Player(const string &name) : Object(name, "Player"){
        this->main_char = MyPolygon(&transformation);
        main_char.add_vert(Point(0, 0));
        main_char.add_vert(Point(-1.5, -3));
        main_char.add_vert(Point(-8, -5));
        main_char.add_vert(Point(-3, -7));
        main_char.add_vert(Point(-2, -9));
        main_char.add_vert(Point(-6, -11));
        main_char.add_vert(Point(-2, -13));
        main_char.add_vert(Point(-4, -25));
        main_char.add_vert(Point(0, -17));
        main_char.add_vert(Point(4, -25));
        main_char.add_vert(Point(2, -13));
        main_char.add_vert(Point(6, -12));
        main_char.add_vert(Point(2, -9));
        main_char.add_vert(Point(3, -6));
        main_char.add_vert(Point(2.5, -4));
        for (int i = 0; i < main_char.size(); i++){
            main_char[i] *= 8;
        }
        main_char.update_bb();

        this->colision_mask.add(MyPolygon(&transformation));
        this->colision_mask.pols.back().add_vert(main_char.rct.mi);
        this->colision_mask.pols.back().add_vert(main_char.rct.a);
        this->colision_mask.pols.back().add_vert(main_char.rct.ma);
        this->colision_mask.pols.back().add_vert(main_char.rct.b);
        this->colision_mask.pols.back().triangulate();
        main_char.triangulate();

        this->move(Point(700, 400));
    }

    void draw(){
        main_char.draw(Color(0, 255, 0));
    }

    void write_debug_information(){
        for (int i = 0; i < this->main_char.triangulation.size(); i++){
            cout << this->main_char.triangulation[i] << "\n";
        }
    }

    void move(const Point &p){
        /*this->main_char.move(p);
        this->colision_mask.move(p);*/
        this->transformation *= get_move_matr(p);
    }

    bool apply_speed(double time){
        this->move(Point(0, g * sqr(time)));
        this->move(this->v * time);
        bool t = false;
        for (int i = 0; i < objs.size(); i++){
            if (objs[i] != this){
                if (colision_types[this->type][objs[i]->type] == "block"){
                    if (is_intersects(objs[i]->colision_mask, this->colision_mask)){
                        t = true;
                        break;
                    }
                }
            }
        }
        if (t){
            this->move(this->v * -time);
            this->move(Point(0, -g * sqr(time)));
            this->apply_acceleration(-time);
            if (ls(EPS, time)){
                this->apply_acceleration(time / 2);
                if (this->apply_speed(time / 2)){
                    this->apply_speed(time / 2);
                }
            }
            this->v = Point();
            return false;
        }
        return true;
    }

    void collision(Object *obj){

    }
};

class Wall : public Object{
public:

    Wall(const string &name) : Object(name, "Wall"){

    }

    void draw(){
        for (int i = 0; i < this->colision_mask.pols.size(); i++){
            this->colision_mask.pols[i].draw(Color(0, 0, 255));
        }
    }
};