#include "MyPolygon.h"

    MyPolygon :: MyPolygon(Matrix *transformation){
        this->transformation = transformation;
        this->verts.clear();
        this->rct = new Rectan(transformation);
        this->update_bb();
    }

    MyPolygon :: MyPolygon(const vector < Point > &verts, Matrix *transformation){
        this->transformation = transformation;
        this->verts = verts;
        this->rct = new Rectan(transformation);
        this->update_bb();
        //this->triangulate();
    }

    void MyPolygon :: update_bb(){
        *this->rct->lb = Point(1e9, 1e9);
        *this->rct->rt = Point(-1e9, -1e9);
        for (int i = 0; i < this->size(); i++){
            this->rct->update_rct((*this)[i]);
        }
    }

    void MyPolygon :: add_vert(const Point &ver){
        this->verts.push_back(ver);
        this->rct->update_rct(ver);
    }

    void MyPolygon :: pop_back(){
        this->verts.pop_back();
    }

    int MyPolygon :: size() const {
        return verts.size();
    }

    Point& MyPolygon :: operator [](int i) {
        //if (i < 0 || i >= size()) return Point(inf, inf);
        //return verts[(i % this->size() + this->size()) % this->size()];
        return verts[(i % this->size() + this->size()) % this->size()];
    }

    Point MyPolygon :: operator [](int i) const {
        //if (i < 0 || i >= size()) return Point(inf, inf);
        //return verts[(i % this->size() + this->size()) % this->size()];
        return verts[(i % this->size() + this->size()) % this->size()];
    }

    Point MyPolygon :: get_val(int i) const {
        return this->verts[(i % this->size() + this->size()) % this->size()];
    }

    Point MyPolygon :: get(int i) const {
        return apply_transformation((*this).get_val(i), *transformation);
    }

    void MyPolygon :: add_transform(const Matrix &m){
        *this->transformation *= m;
    }

    void MyPolygon :: loadFromFile(const string &s){
        FILE *mf;
        mf = freopen(s.c_str(), "r", stdin);
        if (mf == NULL){
            cout << "File not opened\n";
        }
        int n;
        char c;
        //scanf("%d", &n);
        cin >> n;
        //cout << n << "\n";
        this->verts.clear();
        for (int i = 0; i < n; i++){
            long long x, y;
            //scanf("(%lld; %lld)", &x, &y);
            cin >> c >> x >> c >> y >> c;
            this->verts.push_back(Point(x, y));
        }
        fclose(mf);
        cout << "File : " << s << " has loaded\n";
        for (int i = 0; i < n; i++){
            cout << this->verts[i] << "\n";
        }
    }

MyPolygon get_rectangle(double x, double y, double w, double h){
    MyPolygon ans;
    ans.add_vert(Point(x, y));
    ans.add_vert(Point(x + w, y));
    ans.add_vert(Point(x + w, y - h));
    ans.add_vert(Point(x, y - h));
    return ans;
}