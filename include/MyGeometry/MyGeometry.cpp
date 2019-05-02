#include "MyGeometry.h"

/*Vector2i get_relative_mouse_position(RenderWindow &win){
    sf::Vector2i position = sf::Mouse::getPosition();
    Vector2i kek = win.getPosition();
    return Vector2i(position.x - kek.x - 8, HEIGHT - position.y + kek.y + 31);
    //return Vector2i(position.x - kek.x, position.y - kek.y);
}*/

// begin is_intersects

    // without polygon

        bool is_on_segment(const Point &p, const Segment &s){
            //return eq(Segment(s.b, p).len() + Segment(p, s.e).len(), s.len());
            return ls(Point(p, s.getb()) % Point(p, s.gete()), 0) && Line(s).is_on_line(p);
        }

        bool is_intersects(const Circle &c, const Line &l){
            return ls(l.dist(c.p), c.r);
        }
        
        bool is_intersects(const Segment &s, const Circle &c){
            Point pr = Line(s).proj(c.p);
            if (is_on_segment(pr, s)){
                if (ls(Segment(pr, c.p).sqr_len(), sqr(c.r))){
                    if (ls(sqr(c.r), Segment(c.p, s.getb()).sqr_len()) || ls(sqr(c.r), Segment(c.p, s.gete()).sqr_len())){
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                if (lseq(sqr(c.r), Segment(c.p, s.getb()).sqr_len()) && !lseq(sqr(c.r), Segment(c.p, s.gete()).sqr_len())){
                    return true;
                }
            if (!lseq(sqr(c.r), Segment(c.p, s.getb()).sqr_len()) && lseq(sqr(c.r), Segment(c.p, s.gete()).sqr_len())){
                    return true;
                }
                return true;
            }
        }
        
        bool is_intersects(const Circle &c1, const Circle &c2){
            return lseq(
                        sqr(fabs(c1.r - c2.r)), 
                        Segment(c1.p, c2.p).sqr_len())
                    && 
                   lseq(
                        Segment(c1.p, c2.p).sqr_len(), 
                        sqr(fabs(c1.r + c2.r))
                   );
        }

        bool is_intersects(const Line &f, const Line &s){
            return !eq(0, f.v * s.v);
        }

        int intersection_type(const Segment &s, const Line &l){ // O(1)
            /*if (l.is_in_one_half_plane(s.b, s.e) == BOTH_ON_LINE){
                return SEGMENT_LIES_ON_LINE | FIRST_END_LIES_ON_LINE | SECOND_END_LIES_ON_LINE | SEGMENT_INTERSECT_LINE;
            }
            if (l.is_in_one_half_plane(s.b, s.e) == FIRST_ON_LINE){
                return FIRST_END_LIES_ON_LINE | SEGMENT_INTERSECT_LINE;
            }
            if (l.is_in_one_half_plane(s.b, s.e) == SECOND_ON_LINE){
                return SECOND_END_LIES_ON_LINE | SEGMENT_INTERSECT_LINE;
            }
            if (l.is_in_one_half_plane(s.b, s.e) == IN_DIFFERENT_HALF_PLANE){
                return SEGMENT_INTERSECT_LINE;
            }
            if (l.is_in_one_half_plane(s.b, s.e) == IN_SAME_HALF_PLANE){
                return SEGMENT_DOESNT_INTERSECT_LINE;
            }*/
            int ans = 0;
            if (eq(l.get_directional_dist(s.getb()), 0)){
                ans |= BEGIN_LIES_ON_LINE | SEGMENT_INTERSECT_LINE;
            }
            if (eq(l.get_directional_dist(s.gete()), 0)){
                ans |= END_LIES_ON_LINE | SEGMENT_INTERSECT_LINE;
            }
            if ((ans & BEGIN_LIES_ON_LINE) != 0 && (ans & END_LIES_ON_LINE) != 0){
                ans |= SEGMENT_LIES_ON_LINE;
            }
            if (sign(l.get_directional_dist(s.gete())) != sign(l.get_directional_dist(s.getb()))){
                ans |= SEGMENT_INTERSECT_LINE;
            }
            return ans;
        }

        bool is_intersects(const Segment &s, const Line &l){
            return ((intersection_type(s, l) & SEGMENT_INTERSECT_LINE) != 0);
        }

        int intersection_type(const Segment &a, const Segment &b){
            int ans = SEGMENTS_DOESNT_INTERSECT;
            if (intersection_type(b, Line(a)) == SEGMENT_DOESNT_INTERSECT_LINE || intersection_type(a, Line(b)) == SEGMENT_DOESNT_INTERSECT_LINE){
                return SEGMENTS_DOESNT_INTERSECT;
            }
            /*if (intersection_type(b, Line(a)) != SEGMENT_DOESNT_INTERSECT_LINE && intersection_type(b, Line(a)) != SEGMENT_DOESNT_INTERSECT_LINE){
                ans |= SEGMENTS_INTERSECTS;
            }*/
            if (is_on_segment(a.b, b)){
                ans |= FIRST_END_OF_FIRST_LIES_ON_SECOND;
            }
            if (is_on_segment(a.e, b)){
                ans |= SECOND_END_OF_FIRST_LIES_ON_SECOND;
            }
            if ((ans & (FIRST_END_OF_FIRST_LIES_ON_SECOND | SECOND_END_OF_FIRST_LIES_ON_SECOND)) != 0){
                ans |= FIRST_LIES_ON_SECOND;
            }
            if (is_on_segment(b.b, a)){
                ans |= FIRST_END_OF_SECOND_LIES_ON_FIRST;
            }
            if (is_on_segment(b.e, a)){
                ans |= SECOND_END_OF_SECOND_LIES_ON_FIRST;
            }
            if ((ans & (FIRST_END_OF_SECOND_LIES_ON_FIRST | SECOND_END_OF_SECOND_LIES_ON_FIRST)) != 0){
                ans |= SECOND_LIES_ON_FIRST;
            }
            if ((ans & (FIRST_LIES_ON_SECOND | FIRST_LIES_ON_SECOND)) != 0){
                ans |= SEGMENTS_ARE_EQUAL;
            }
            if (ans > 0 || (intersection_type(b, Line(a)) == SEGMENT_INTERSECT_LINE && intersection_type(a, Line(b)) == SEGMENT_INTERSECT_LINE)){
                ans |= SEGMENTS_INTERSECTS;
            }
            return ans;
        }

        bool is_intersects(const Segment &f, const Segment &s){ // O(1) touching by ends of segments will return false
            if (f.getb() == s.getb() || f.gete() == s.gete() || f.getb() == s.gete() || f.gete() == s.getb()) return false;
            return (is_intersects(s, Line(f))) && (is_intersects(f, Line(s)));
        }

    // without polygon


    // with rectan

        bool is_in(const Point &p, const Rectan &r){
            return (lseq(r.get_lb().x, p.x) && lseq(p.x, r.get_rt().x) && lseq(r.get_lb().y, p.y) && lseq(p.y, r.get_rt().y));
        }

        bool is_in(const Segment &s, const Rectan &r){
            return is_in(s.getb(), r) || is_in(s.gete(), r);
        }

        bool is_in(const MyPolygon &p, const Rectan &r){
            return is_in(p[0], r);
        }

        bool is_intersects(const Rectan &r1, const Rectan &r2){
            if (is_intersects(Segment(r1.get_lb(), r1.get_lt()), r2)) return true;
            if (is_intersects(Segment(r1.get_lt(),  r1.get_rt()), r2)) return true;
            if (is_intersects(Segment(r1.get_rt(), r1.get_rb()), r2)) return true;
            if (is_intersects(Segment(r1.get_rb(),  r1.get_lb()), r2)) return true;
            return is_in(r1.get_lb(), r2) || is_in(r2.get_lb(), r1);
        }

    // with rectan


    // with polygon

        bool intersect_checker_like_segment(const Segment &a, const Segment &b){
            return (intersection_type(a, b) & SEGMENTS_INTERSECTS) > 0;
        }

        bool intersect_checker_like_interval(const Segment &a, const Segment &b) {
            if (!intersect_checker_like_segment(a, b)) return false;
            if (a.b == b.b || a.b == b.e || a.e == b.b || a.e == b.e) return false;
            return true;
        }

        bool is_intersects(const Segment &s, const MyPolygon &p, bool (*intersect_checker)(const Segment &, const Segment &)){
            if (!is_intersects(s, *p.rct)) return false;
            for (int i = 0; i < p.size(); i++){
                if (intersect_checker(Segment(p.get(i), p.get(i + 1)), s)) return true;
            }
            return false;
        }

        /*template < class T >
        bool is_intersects(MyPolygon &pol, T &x){
            return is_intersects(x, pol);
        }*/

        bool is_intersects(const MyPolygon &x, const MyPolygon &pol){
            if (!is_intersects(*pol.rct, *x.rct)) return false;
            for (int i = 0; i < pol.size(); i++){
                if (is_intersects(Segment(pol.get(i), pol.get(i + 1)), x)) return true;
            }
            return false;
        }

    // with polygon

    bool is_intersects(const ComplexShape &cs1, const ComplexShape &cs2){
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

    // Ray

    bool is_intersects(const Ray &r, const Segment &s){
        
        if (!is_intersects(s, Line(r.b, r.b + r.v))) return false;

        Point tmp = get_intersection(Line(s), Line(r.b, r.b + r.v));
        /*cout << "in is_intersects ";
        cout << r.b << " " << r.v << "\n";
        cout << s.b << " " << s.e << "\n";
        cout << tmp << "\n";*/
        return r.is_on_ray(tmp);
    }


    // copies

    /*template < class T1, class T2 >
    bool is_intersects(T1 x, T2 y){
        return is_intersects(y, x);
    }*/

    // copies


// end is_intersects



double Segment :: dist_to(const Point &p){
    if (is_on_segment(Line(this->b, this->e).proj(p), *this)){
        return Line(this->b, this->e).get_directional_dist(p);
    }
    return min(Point(this->b, p).len(), Point(this->e, p).len());
}


bool FlatAngle :: is_in(const Point &p) const {
    return !is_intersects(Segment(p, this->c), Line(this->a, this->b)) &&
            !is_intersects(Segment(p, this->a), Line(this->c, this->b));
}

bool is_in(const Point &p, const MyPolygon &pol){
    if (!is_in(p, *pol.rct)) return false;
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

//get_intersection

Point get_intersection(const Line &f, const Line &s){
    Color fabc = f.get_abc();
    Color sabc = s.get_abc();
    return Point(
        -(
            (fabc.b * sabc.g - fabc.g * sabc.b) /
            (fabc.r * sabc.g - fabc.g * sabc.r)
        ),
        -(
            (fabc.r * sabc.b - fabc.b * sabc.r) /
            (fabc.r * sabc.g - fabc.g * sabc.r)
        )
    );
}

Point get_intersection(const Line &l, const Segment &s){
    return get_intersection(l, Line(s));
}

Point get_intersection(const Ray &r, const Segment &s){
    return get_intersection(Line(r.b, r.b + r.v), Line(s.getb(), s.gete()));
}

// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE
// NOW NOT AVAILABLE

    /*

    Segment get_intersection(const Segment &f, const Segment &s){
        Segment f_ = f, s_ = s;
        if (is_intersects(Line(f_), Line(s_))){
            return Segment(get_intersection(Line(f_), Line(s_)), get_intersection(Line(f_), Line(s_)));
        } else {
            Segment ans;
            if (f_.b > f_.e){
                swap(f_.b, f_.e);
            }
            if (s_.b > s_.e){
                swap(s_.b, s_.e);
            }
            ans.b = max(f_.b, s_.b);
            ans.e = min(f_.e, s_.e);
            return ans;
        }
    }

    pair < Point, Point > get_intersection(const Line &l, const Circle &c){
        Point pr = l.proj(c.p);
        Angle a = Angle().set_as_rad(acos(c.r / l.dist(c.p)));
        Point v(c.p, pr);
        return make_pair(v.rot(a), v.rot(-a));
    }

    pair < Point, Point > get_intersection(const Circle &c, const Line &l){
        return get_intersection(l, c);
    }

    pair < Point, Point > get_intersection(const Segment &s, const Circle &c){
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

    pair < Point, Point > get_intersection(const Circle &c, const Segment &s){
        return get_intersection(s, c);
    }*/

//get_intersection








bool is_good(const MyPolygon &p, const Segment &s){
    return !is_intersects(s, p) && is_in(Point(s.getb(), s.gete()) / 2 + s.getb(), p);
}

void MyPolygon :: triangulate(){
    //if (this->triangulated) return;
    //this->triangulated = true;
    //if (this->size() < 3) return;
    //MyPolygon now = *this;
    vector < int > used(this->size(), 0);
    int prev = 0;
    int now = 1;
    int next = 2;
    this->triangulation.clear();
    while (this->triangulation.size() < this->size() - 2){\
        if (is_good(*this, Segment(this->get(prev), this->get(next)))){// && !eq(Point(this->get(now), this->get(prev)) * Point(this->get(now),this->get(next)), 0)){
            this->triangulation.push_back(
                Triangle(
                    (*this)[prev], 
                    (*this)[now], 
                    (*this)[next], 
                    this->transformation
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



float MyPolygon :: getArea(){
    this->area = 0;
    for (int i = 0; i < this->size(); i++){
        this->area += ((*this)[i] - (*this)[i + 1]) * ((*this)[i + 2] - (*this)[i + 1]);
    }
    this->area /= 2;
    return this->area;
}

bool vector_cmp(const Point &a, const Point &b){
    if (ls(0, a.x) && ls(b.x, 0)) return true;
    if (ls(a.x, 0) && ls(0, b.x)) return false;
    if (ls(0, a.x)){
        if (a.y < 0 && b.y > 0) return true;
        if (a.y > 0 && b.y < 0) return false;
    } else if (a.x < 0){
        if (a.y < 0 && b.y > 0) return false;
        if (a.y > 0 && b.y < 0) return true;
    }
    if (eq(a * b, 0)){
        return ls(a.sqr_len(), b.sqr_len());
    }
    return ls(0, a * b);
}

bool in_good_order(const Point &a, const Point &b, const Point &c){
    return vector_cmp(Point(a * b / a.len(), a % b / a.len() * -1), Point(a * c / a.len(), a % c / a.len() * -1));
}

bool mx_conv_cmp(const pair < Point, pair < int, int > > &a, const pair < Point, pair < int, int > > &b){
    return vector_cmp(a.first, b.first);
}

vector < int > max_convex_underpolygon(const MyPolygon &p){
    int n = p.size();
    vector < pair < Point, pair < int, int > > > tmp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            Segment temp = Segment(apply_transformation(p[i], *p.transformation), apply_transformation(p[j], *p.transformation));
            if (abs(i - j) == 1 || (i != j && !is_intersects(temp, p, intersect_checker_like_interval) 
                && in_good_order(Point(p[i], p[i + 1]), Point(p[i], p[j]), Point(p[i], p[i - 1])))){
                tmp.push_back(make_pair(Point(p[i], p[j]), make_pair(i, j)));
            }
        }
    }
    // sort tmp by angle 
    sort(tmp.begin(), tmp.end(), mx_conv_cmp);
    vector < int > ans;
    for (int i = 0; i < n; i++){
        vector < int > dp(n, -1), temp;
        vector < vector < pair < int, int > > > pr(n);
        pr[i].push_back(make_pair(i, 0));
        dp[i] = 1;
        for (int j = 0; j < tmp.size(); j++){
            if (dp[tmp[j].second.first] != -1 && 
                lseq(p[i].x, p[tmp[j].second.first].x) && 
                lseq(p[i].x, p[tmp[j].second.second].x)){

                if (dp[tmp[j].second.second] < dp[tmp[j].second.first] + 1){
                    dp[tmp[j].second.second] = dp[tmp[j].second.first] + 1;
                    pr[tmp[j].second.second].push_back(make_pair(tmp[j].second.first, pr[tmp[j].second.first].size() - 1));
                }

            }
        }
        if (pr[i].size() > 1){
            pair < int, int > now = pr[i].back();
            while (now.first != i){
                temp.push_back(now.first);
                now = pr[now.first][now.second];
            }
            temp.push_back(now.first);
            if (temp.size() > ans.size()){
                ans = temp;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

ConvexPolygons PolygonDecomposition(const MyPolygon &p){
    int l = 0;
    ConvexPolygons ans;
    vector < int > tmp = max_convex_underpolygon(p);
    MyPolygon max_underpolygon;
    for (int i = 0; i < tmp.size(); i++){
        max_underpolygon.add_vert(p.get(tmp[i]));
    }
    while (l != tmp[0]) l++;
    for (int i = 1; i < tmp.size(); i++){
        MyPolygon temp;
        while (l != tmp[i]){
            temp.add_vert(p.get(l));
            l++;
        }
        temp.add_vert(p.get(l));
        if (temp.size() > 2){
            ans = ans + PolygonDecomposition(temp);
        }
    }
    return ans;
}