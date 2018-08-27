#include "MyComplexShape.h"

/*Vector2i get_relative_mouse_position(RenderWindow &win){
    sf::Vector2i position = sf::Mouse::getPosition();
    Vector2i kek = win.getPosition();
    return Vector2i(position.x - kek.x - 8, HEIGHT - position.y + kek.y + 31);
    //return Vector2i(position.x - kek.x, position.y - kek.y);
}*/

// is_intersects

    // without polygon

        bool is_intersects(Point &p, Segment &s){
            return eq(Segment(s.b, p).len() + Segment(p, s.e).len(), s.len());
        }

        bool is_intersects(Circle &c, Line &l){
            return ls(l.dist(c.p), c.r);
        }

        bool is_intersects(Segment &s, Circle &c){
            Point pr = Line(s).proj(c.p);
            if (is_intersects(pr, s)){
                if (ls(Segment(pr, c.p).sqr_len(), sqr(c.r))){
                    if (ls(sqr(c.r), Segment(c.p, s.b).sqr_len()) || ls(sqr(c.r), Segment(c.p, s.e).sqr_len())){
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                if (lseq(sqr(c.r), Segment(c.p, s.b).sqr_len()) && !lseq(sqr(c.r), Segment(c.p, s.e).sqr_len())){
                    return true;
                }
                if (!lseq(sqr(c.r), Segment(c.p, s.b).sqr_len()) && lseq(sqr(c.r), Segment(c.p, s.e).sqr_len())){
                    return true;
                }
                return true;
            }
        }
        
        bool is_intersects(Circle &c1, Circle &c2){
            return lseq(
                        sqr(fabs(c1.r - c2.r)), 
                        Segment(c1.p, c2.p).sqr_len())
                    && 
                   lseq(
                        Segment(c1.p, c2.p).sqr_len(), 
                        sqr(fabs(c1.r + c2.r))
                   );
        }

        bool is_intersects(Line &f, Line &s){
            return !eq(0, f.v * s.v);
        }

        bool is_intersects(Segment &s, Line &l){ // O(1)
            return !l.is_in_one_half_plane(s.b, s.e);
        }

        bool is_intersects(Segment &f, Segment &s){ // O(1)
            if (f.b == s.b || f.e == s.e || f.b == s.e || f.e == s.b) return false;
            return (is_intersects(s, Line(f))) && (is_intersects(f, Line(s)));
        }

    // without polygon


    // with rectan

        template < class T >
        bool is_intersects(T &r2, Rectan &r1){
            if (is_intersects(Segment(r1.getmi(), r1.geta()), r2)) return true;
            if (is_intersects(Segment(r1.geta(),  r1.getma()), r2)) return true;
            if (is_intersects(Segment(r1.getma(), r1.getb()), r2)) return true;
            if (is_intersects(Segment(r1.getb(),  r1.getmi()), r2)) return true;
            return false;
        }

        template < class T >
        bool is_intersects(Rectan &r, T &x){
            return is_intersects(x, r);
        }
        
        bool is_intersects(Rectan &r, Point &p){
            return (ls(r.getmi().x, p.x) && ls(p.x, r.getma().x) && ls(r.getmi().y, p.y) && ls(p.y, r.getma().y));
        }

        bool is_intersects(Point &p, Rectan &r){
            return is_intersects(r, p);
        }

        bool is_intersects(Rectan &r1, Rectan &r2){
            if (is_intersects(Segment(r1.getmi(), r1.geta()), r2)) return true;
            if (is_intersects(Segment(r1.geta(),  r1.getma()), r2)) return true;
            if (is_intersects(Segment(r1.getma(), r1.getb()), r2)) return true;
            if (is_intersects(Segment(r1.getb(),  r1.getmi()), r2)) return true;
            return false;
        }

    // with rectan


    // with polygon

        template < class T >
        bool is_intersects(T &x, MyPolygon &pol){
            if (!is_intersects(pol.rct, x)) return false;
            for (int i = 0; i < pol.size(); i++){
                if (is_intersects(Segment(pol.get(i), pol.get(i + 1)), x)) return true;
            }
            return false;
        }

        /*template < class T >
        bool is_intersects(MyPolygon &pol, T &x){
            return is_intersects(x, pol);
        }*/

        bool is_intersects(MyPolygon &x, MyPolygon &pol){
            if (!is_intersects(pol.rct, x.rct)) return false;
            for (int i = 0; i < pol.size(); i++){
                if (is_intersects(Segment(pol.get(i), pol.get(i + 1)), x)) return true;
            }
            return false;
        }

    // with polygon

    bool is_intersects(ComplexShape &cs1, ComplexShape &cs2){
        for (int i = 0; i < cs1.pols.size(); i++){
            for (int j = 0; j < cs2.pols.size(); j++){
                if (is_intersects(cs1.pols[i], cs2.pols[j])) return true;
            }
        }
        for (int i = 0; i < cs1.pols.size(); i++){
            for (int j = 0; j < cs2.circles.size(); j++){
                if (is_intersects(cs2.circles[j], cs1.pols[i])) return true;
            }
        }
        for (int i = 0; i < cs1.circles.size(); i++){
            for (int j = 0; j < cs2.pols.size(); j++){
                if (is_intersects(cs1.circles[i], cs2.pols[j])) return true;
            }
        }
        for (int i = 0; i < cs1.circles.size(); i++){
            for (int j = 0; j < cs2.circles.size(); j++){
                if (is_intersects(cs1.circles[i], cs2.circles[j])) return true;
            }
        }
        return false;
    }


    // copies

    /*template < class T1, class T2 >
    bool is_intersects(T1 x, T2 y){
        return is_intersects(y, x);
    }*/

    // copies


// is_intersects

bool is_in(Point &p, MyPolygon &pol){
    if (!is_intersects(pol.rct, p)) return false;
    bool ans = false;
    int n = pol.size();
    Segment ray(p, Point(inf, 1));
    for (int i = 1; i <= n; i++){
        Point b = pol.get(i - 1);
        Point e = pol.get(i);
        Segment seg(b, e);
        if (is_intersects(seg, ray)){
            ans ^= 1;
        }
    }
    return ans;
}

bool is_in(MyPolygon &pol, Point &p){
    return is_in(p, pol);
}

//get_intersection

    Point get_intersection(Line &f, Line &s){
        double b = (f.p * f.v + f.v * s.p) / (s.v * f.v);
        return f.p + f.v * b;
    }

    Point get_intersection(Line &l, Segment &s){
        return get_intersection(l, Line(s));
    }

    Point get_intersection(Segment &s, Line &l){
        return get_intersection(l, Line(s));
    }

    Segment get_intersection(Segment &f, Segment &s){
        if (is_intersects(Line(f), Line(s))){
            return Segment(get_intersection(Line(f), Line(s)), get_intersection(Line(f), Line(s)));
        } else {
            Segment ans;
            if (f.b > f.e){
                swap(f.b, f.e);
            }
            if (s.b > s.e){
                swap(s.b, s.e);
            }
            ans.b = max(f.b, s.b);
            ans.e = min(f.e, s.e);
            return ans;
        }
    }

    pair < Point, Point > get_intersection(Line &l, Circle &c){
        Point pr = l.proj(c.p);
        Angle a = Angle().set_as_rad(acos(c.r / l.dist(c.p)));
        Point v(c.p, pr);
        return make_pair(v.rot(a), v.rot(-a));
    }

    pair < Point, Point > get_intersection(Circle &c, Line &l){
        return get_intersection(l, c);
    }

    pair < Point, Point > get_intersection(Segment &s, Circle &c){
        //Point pr = Line(s).proj(c.p);
        pair < Point, Point > p = get_intersection(Line(s), c);
        if (is_intersects(p.first, s) && is_intersects(p.second, s)){
            return p;
        }
        if (is_intersects(p.first, s)){
            return make_pair(p.first, p.first);
        }
        if (is_intersects(p.second, s)){
            return make_pair(p.second, p.second);
        }
        return make_pair(Point(), Point());
    }

    pair < Point, Point > get_intersection(Circle &c, Segment &s){
        return get_intersection(s, c);
    }

//get_intersection






// useless function
bool is_realy_intersects(Segment &f, Segment &s){
    if (is_intersects(f, s)){
        Segment intr = get_intersection(f, s);
        return (intr.b <= intr.e);
    }
    return false;
}
// useless function

// another useless function
bool is_ear(MyPolygon &p, int x){ // O(n)
    return !is_intersects(Segment(p.get(x - 1), p.get(x + 1)), p) && is_in(p, Point(p.get(x - 1), p.get(x + 1)) / 2 + p.get(x - 1));
}
// another useless function

bool is_good(MyPolygon &p, Segment &s){
    return !is_intersects(s, p) && is_in(p, Point(s.b, s.e) / 2 + s.b);
}

void MyPolygon :: triangulate(){
    if (this->triangulated) return;
    this->triangulated = true;
    if (this->size() < 3) return;
    //MyPolygon now = *this;
    vector < int > used(this->size(), 0);
    int prev = 0;
    int now = 1;
    int next = 2;
    this->triangulation.clear();
    while (this->triangulation.size() < this->size() - 2){
        if (is_good(*this, Segment(this->get(prev), this->get(next))) && !eq(Point(this->get(now), this->get(prev)) * Point(this->get(now),this->get(next)), 0)){
            this->triangulation.push_back(
                Triangle(
                    this->transformation,
                    (*this)[prev], 
                    (*this)[now], 
                    (*this)[next], 
                    prev % this->size(), 
                    now % this->size(), 
                    next % this->size()
                )
            );
            used[now % this->size()] = 1;
            now = next;
            next++;
            while (used[next % this->size()] == 1) next++;
        } else {
            prev = now;
            now = next;
            next++;
            while (used[next % this->size()] == 1) next++;
        }
    }
    //this->triangulation.push_back(Triangle(now[l - 1), now[l), now[l + 1]));
}

