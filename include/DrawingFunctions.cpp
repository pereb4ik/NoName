#include "DrawingFunctions.h"

/*void add_gl_point(const Point &a, const Color &fillColor){
    //glColor3f(fillColor.r / 255.f, fillColor.g / 255.f, fillColor.b / 255.f);
    //glVertex3f((float)to_gl_coords(a).x, (float)to_gl_coords(a).y, 0.f);
    //glVertex2f((float)to_gl_coords(a).x, (float)to_gl_coords(a).y);
}*/


void add_normal_gl_point(const Point &p){
    glVertex2d(p.x, p.y);
}

void add_gl_point(const Point &p){
    //glVertex2d(scrx % Point(scrLB, p), scry % Point(scrLB, p));
    glVertex2d((Point(scrLB, p) * scry) / (scrx * scry), (Point(scrLB, p) * scrx) / (scry * scrx));
}

MyPolygon get_screen(){
    MyPolygon ans;
    ans.add_vert(scrLB);
    ans.add_vert(scrLB + scrx * WIDTH);
    ans.add_vert(scrLB + scrx * WIDTH + scry * HEIGHT);
    ans.add_vert(scrLB + scry * HEIGHT);
    return ans;
}

void add_gl_color(const Color &c){
    glColor4f(c.r / 255, c.g / 255, c.b / 255, c.a / 255);
}

void Segment :: draw(const Color &c){
    glLineWidth(2.5); 
    //glColor3f(1.0, 0.0, 0.0);
    add_gl_color(c);
    glBegin(GL_LINES);
    add_gl_point(this->getb());
    add_gl_point(this->gete());
    glEnd();
    /*sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(getb().x - Camera.get_abs_pos().x, HEIGHT - getb().y - Camera.get_abs_pos().y)),
        sf::Vertex(sf::Vector2f(gete().x - Camera.get_abs_pos().x, HEIGHT - gete().y - Camera.get_abs_pos().y))
    };

    window.draw(line, 2, sf::Lines);*/
}

void draw_triangle(const Point &a, const Point &b, const Point &c, const Color &fillColor){
    glBegin(GL_TRIANGLES);
    /*glVertex3f((float)to_gl_coords(a).x, (float)to_gl_coords(a).y, 0.f);
    glVertex3f((float)to_gl_coords(b).x, (float)to_gl_coords(b).y, 0.f);
    glVertex3f((float)to_gl_coords(c).x, (float)to_gl_coords(c).y, 0.f);*/
    add_gl_color(fillColor);
    add_gl_point(a);
    add_gl_point(b);
    add_gl_point(c);
    glEnd();
}

void Triangle :: draw(const Color &c){
    draw_triangle(this->get_a(), this->get_b(), this->get_c(), c);
}

void MyPolygon :: draw_edges(const Color &c){
    for (int i = 0; i < this->size(); i++){
        add_to_draw(Segment(this->get(i), this->get(i + 1)), c);//.draw(c);
        /*add_vert(this->get(i));
        add_vert(this->get(i + 1));*/
    }
}

void MyPolygon :: draw_area(const Color &fill_color, const double &thickness, const Color &outline_color){
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < this->triangulation.size(); i++){
        //this->triangulation[i].draw(fill_color);
        draw_triangle(
            this->triangulation[i].get_a(),
            this->triangulation[i].get_b(),
            this->triangulation[i].get_c(),
            fill_color
        );
    }
    glEnd();
}

/*void Triangle :: draw(const Color &fillColor){
    draw_triangle(*a, *b, *c); 
}*/

/*void ConvexPolygons :: draw(const Color &c){
    for (int i = 0; i < this->size(); i++){
        (*this)[i].draw(c);
    }
}*/

vector < pair < Segment, Color > > globalDrawingSegmentVector;

void add_to_draw(const Segment &s, const Color &c){
    globalDrawingSegmentVector.push_back(make_pair(s, c));
}

Point pointOfView;

bool SegmentComparator(pair < Segment, Color > a, pair < Segment, Color > b){
    //if (
        return min(Point(a.first.b, pointOfView).sqr_len(), Point(a.first.e, pointOfView).sqr_len()) > min(Point(b.first.b, pointOfView).sqr_len(), Point(b.first.e, pointOfView).sqr_len());
        //return false;
    //}
}

Point basic_vect, begin_point;
bool by_angle(Point a, Point b){
    return in_good_order(basic_vect, Point(begin_point, a), Point(begin_point, b));
}

void drawSegments(const Point &pOV){
    pointOfView = pOV;
    glLineWidth(5);
    glBegin(GL_LINES);
    sort(globalDrawingSegmentVector.begin(), globalDrawingSegmentVector.end(), SegmentComparator);
    int n = globalDrawingSegmentVector.size();
    if (n > 0){
        for (int i = 0; i < n; i++){
            Segment *s = &globalDrawingSegmentVector[i].first;

            add_gl_color(globalDrawingSegmentVector[i].second);
            //add_gl_color(Color(255. * i / n, 0, 0, 255));

            add_gl_point(s->getb());
            add_gl_point(s->gete());
        }
    }
    glEnd();
    if (n > 0){
        add_gl_color(Color(0, 0, 0, 255));
        MyPolygon tmp = get_screen();
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < n; i++){
            Segment s = globalDrawingSegmentVector[i].first;
            if (ls(Point(pOV, s.b) * Point(pOV, s.e), 0)) swap(s.b, s.e);
            FlatAngle fa = FlatAngle(s.getb(), pOV, s.gete());
            vector < Point > kek;
            for (int j = 0; j < tmp.size(); j++){
                if (is_intersects(Ray(pOV, s.getb()), Segment(tmp[j], tmp[j + 1]))){
                    kek.push_back(get_intersection(Ray(pOV, s.getb()), Segment(tmp[j], tmp[j + 1])));
                }
            }
            for (int j = 0; j < tmp.size(); j++){
                if (fa.is_in(tmp[j])){
                    kek.push_back(tmp[j]);
                }
            }
            for (int j = 0; j < tmp.size(); j++){
                if (is_intersects(Ray(s.gete(), s.gete() * 2 - pOV), Segment(tmp[j], tmp[j + 1]))){
                    kek.push_back(get_intersection(Ray(pOV, s.gete()), Segment(tmp[j], tmp[j + 1])));
                }
            }
            
            begin_point = pOV;
            basic_vect = Point(pOV, s.getb());
            sort(kek.begin(), kek.end(), by_angle);
            kek.push_back(s.gete());
            for (int j = 1; j < kek.size(); j++){
                //add_gl_color(Color(0, 0, 255. * j / kek.size(), 128));
                add_gl_point(s.getb());
                add_gl_point(kek[j - 1]);
                add_gl_point(kek[j]);
            }
        }
        glEnd();
    }

}