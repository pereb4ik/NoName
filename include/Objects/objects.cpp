#include "objects.h"

    // RisingTriangle

    RisingTriangle :: RisingTriangle(const string &name) : Object(name, "RisingTriangle"){
        now = Point(200, 50);
    }

    void RisingTriangle :: draw(){
        glBegin(GL_TRIANGLES);
        add_gl_point(now);
        add_gl_point(now + Point(10, 20));
        add_gl_point(now + Point(20, 10));
        /*glVertex2f((float)x, (float)y);
        glVertex2f((float)x + 10, (float)y + 20);
        glVertex2f((float)x + 20, (float)y + 10);*/
        glEnd();
    }

    void RisingTriangle :: every_frame(){
        now += Point(0, 10);
        now.y = (int)(now.y - (int)(now.y / HEIGHT) * HEIGHT);
    }

    // Cursor

    void Cursor :: draw(){
        Matrix tmp = *cursor.transformation;
        *cursor.transformation *= get_move_matr(cur);

        glBegin(GL_TRIANGLES);
        add_gl_color(Color(0, 255, 0));
        for (int i = 0; i < this->cursor.triangulation.size(); i++){
            //this->triangulation[i].draw(fill_color);
            add_normal_gl_point(this->cursor.triangulation[i].get_a());
            add_normal_gl_point(this->cursor.triangulation[i].get_b());
            add_normal_gl_point(this->cursor.triangulation[i].get_c());
        }
        glEnd();
        add_gl_color(Color(255, 0, 255));
        glLineWidth(2);
        glBegin(GL_LINES);
        for (int i = 0; i < this->cursor.size(); i++){
            add_normal_gl_point(this->cursor.get(i));
            add_normal_gl_point(this->cursor.get(i + 1));
            //Segment(this->get(i), this->get(i + 1)).draw(c);
        }
        glEnd();

        *cursor.transformation = tmp;
    }

    Cursor :: Cursor(const string &name) : Object(name, "Cursor"){
        cursor.add_vert(Point(0, 2)      );
        cursor.add_vert(Point(0, 1)      );
        cursor.add_vert(Point(0.27, 1.36));
        cursor.add_vert(Point(0.27, 1.36));
        cursor.add_vert(Point(0.35, 0.65));
        cursor.add_vert(Point(0.71, 0.79));
        cursor.add_vert(Point(0.27, 1.36));
        cursor.add_vert(Point(0.71, 1.29));
        cursor.add_vert(Point(0, 2)      );
        cursor.update_bb();
        cursor.triangulate();

        *cursor.transformation *= get_move_matr(-cursor[0]);
        *cursor.transformation *= get_hom_matr(20);
    }

    void Cursor :: every_frame(){}

    // RotatingTriangle

    RotatingTriangle :: RotatingTriangle(const string &name) : Object(name, "RotatingTriangle"){
        ss_rot_center = Point(300, 300);
        r = 50;
        asspeed.set_as_deg(360);
        asrotspeed.set_as_deg(180);
        ss.add_vert(Point());
        ss.add_vert(Point(50, 0));
        ss.add_vert(Point(0, 50));
        *ss.transformation *= get_move_matr(ss_rot_center + Point(r, 0));
    }

    void RotatingTriangle :: draw(){
        ss.draw_edges(Color(32, 64, 128));
    }

    void RotatingTriangle :: every_frame(){
        *ss.transformation *= get_rot_matr(asrotspeed * delta_time, ss_rot_center);
        *ss.transformation *= get_rot_matr(asspeed * delta_time, apply_transformation(ss_center, *ss.transformation));
    }

    // arrow

    Arrow :: Arrow(const string &name) : Object(name, "Arrow"){
        a = Point(200, 200);
        b = Point(300, 200);
        to = Point(250, 500);
    }

    void Arrow :: draw(){
        vector < Point > ar;
        Point m = (a + b) / 2;
        ar.push_back((m + to) / 2);
        ar.push_back(a + (to - a) * 3 / 8);
        ar.push_back(m + (to - m) * 7 / 16);

        ar.push_back(m + (to - m) * 7 / 16);
        ar.push_back(a);
        ar.push_back(m + (to - m) / 8);

        ar.push_back(m + (to - m) / 8);
        ar.push_back(b);
        ar.push_back(m + (to - m) * 7 / 16);

        ar.push_back(m + (to - m) * 7 / 16);
        ar.push_back(b + (to - b) * 3 / 8);
        ar.push_back((m + to) / 2);

        add_gl_color(Color(147, 112, 219));
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < ar.size(); i++){
            add_gl_point(ar[i]);
        }
        glEnd();

        
    }

    // LoadedPolygon

    LoadedPolygon :: LoadedPolygon(const string &name) : Object(name, "LoadedPolygon"){
        this->pol.loadFromFile("Polygons/PolygonDataFile.polygon");
    }

    void LoadedPolygon :: draw(){
        this->pol.draw_edges(Color("FF8C00"));
    }