#include "MyCircle.h"

class MyPolygon{
public:
    vector < Point > verts;
    vector < Triangle > triangulation;
    Rectan rct;
    bool triangulated;
    Matrix *transformation;

    MyPolygon(Matrix *transformation = new Matrix(get_ide_matr(3))){
        this->transformation = transformation;
        this->verts.clear();
        this->update_bb();
        this->triangulated = true;
    }

    MyPolygon(const vector < Point > &verts, Matrix *transformation = new Matrix(get_ide_matr(3))){
        this->transformation = transformation;
        this->verts = verts;
        this->update_bb();
        //this->triangulate();
        this->triangulated = true;
    }

    void update_bb(const Point &x){
        rct.mi.x = min(rct.mi.x, x.x);
        rct.mi.y = min(rct.mi.y, x.y);
        rct.ma.x = max(rct.ma.x, x.x);
        rct.ma.y = max(rct.ma.y, x.y);
        rct = Rectan(rct.mi, rct.ma, this->transformation);
    }

    void update_bb(){
        this->rct.mi = Point(1e9, 1e9);
        this->rct.ma = Point(-1e9, -1e9);
        for (int i = 0; i < this->size(); i++){
            this->update_bb((*this)[i]);
        }
    }

    void triangulate();

    void add_vert(const Point &ver){
        this->verts.push_back(ver);
        this->update_bb(ver);
        this->triangulated = false;
    }

    void pop_back(){
        this->verts.pop_back();
        this->triangulated = false;
    }

    int size(){
        return verts.size();
    }

    inline Point& MyPolygon::operator [](int i){
        //if (i < 0 || i >= size()) return Point(inf, inf);
        //return verts[(i % this->size() + this->size()) % this->size()];
        return verts[(i % this->size() + this->size()) % this->size()];
    }

    Point get(int i){
        return apply_transformation((*this)[i], transformation);
    }

    void rot(const Angle &agl, const Point &p = Point()){
        *this->transformation *= get_rot_matr(agl.get_as_rad(), p);

        /*for (int i = 0; i < this->size(); i++){
            //ans.add_vert(this->verts[0] + this->origin_point + Point(this->verts[0] + this->origin_point, this->verts[i]).get_turned_by_angle(agl));
            this->verts[i] = p + Point(p, this->verts[i]).rot(agl);
        }*/
    }

    void move(const Point &v){
        *this->transformation *= get_move_matr(v);
        /*this->rct.move(v);
        for (int i = 0; i < this->size(); i++){
            this->verts[i] += v;
        }
        for (int i = 0; i < this->triangulation.size(); i++){
            this->triangulation[i].move(v);
        }*/
    }

    void draw(const Color &, const double &, const Color &);
};

MyPolygon get_rectangle(double x, double y, double w, double h){
    MyPolygon ans;
    ans.add_vert(Point(x, y));
    ans.add_vert(Point(x + w, y));
    ans.add_vert(Point(x + w, y - h));
    ans.add_vert(Point(x, y - h));
    return ans;
}
