#include "StandartIncludes.h"
#include "MyMatrixes.h"

Matrix :: Matrix () {}

Matrix :: Matrix (const vector < vector < double > > &mtr) {
    matr = mtr;
    n = mtr.size();
    m = mtr[0].size();
}

Matrix :: Matrix (const vector < double > &mtr) {
    matr.clear();
    matr.push_back(mtr);
    n = 1;
    m = mtr.size();
}

Matrix :: Matrix (const Point &p) {
    vector < double > tmp;
    tmp.push_back(p.x);
    tmp.push_back(p.y);
    matr.clear();
    matr.push_back(tmp);
    n = 1;
    m = tmp.size();
}

vector < double > &Matrix :: operator [](const int &i) {
    if (i < 0 || i >= n) {
        cout << "ERROR, see: vector < double > & Matrix::operator [](int i) in MyMatrixes.h";
        system("pause");
        exit(1);
    }
    return matr[i];
}

vector < double > Matrix :: operator [](const int &i) const {
    if (i < 0 || i >= n) {
        cout << "ERROR, see: vector < double > & Matrix::operator [](int i) in MyMatrixes.h";
        system("pause");
        exit(1);
    }
    return matr[i];
}

/*vector < double > get(const int &i) const {
    if (i < 0 || i >= n) {
        cout << "ERROR, see: vector < double > get(const int &i) const in MyMatrixes.h";
        system("pause");
        exit(1);
    }
    return matr[i];
}*/

Point Matrix :: get_as_point(){
    return Point(matr[0][0], matr[0][1]);
}

vector < double > Matrix :: get_as_vector(){
    return matr[0];
}

Matrix operator * (const Matrix &m1, const Matrix &m2) {
    if (m1.m != m2.n) {
        cout << "ERROR, see: Matrix operator * (const Matrix &m1, const Matrix &m2) in MyMatrixes.cpp";
        system("pause");
        exit(1);
        return Matrix();
    }
    Matrix ans(
            vector < vector < double > > (
                m1.n, 
                vector < double > (m2.m, 0)
            )
        );
    for (int i = 0; i < m1.n; i++){
        for (int j = 0; j < m2.m; j++){
            for (int k = 0; k < m1.m; k++){
                ans[i][j] += (m1[i][k] * m2[k][j]);
            }
        }
    }
    return ans;
}

Matrix &operator *= (Matrix &a, const Matrix &b){
    return a = a * b;
}

Matrix get_ide_matr(const int &n) {
    Matrix tmp( vector < vector < double > > ( n, vector < double > ( n, 0 ) ) );
    //vector < vector < double > > mtr(n, vector < double > (n, 0));
    for (int i = 0; i < n; i++){
        tmp[i][i] = 1;
    }
    return tmp;
}

Matrix get_move_matr(const Point &p/* = Point()*/) {
    Matrix ans = get_ide_matr(3);
    ans[2][0] = p.x;
    ans[2][1] = p.y;
    return ans;
}

/*Matrix get_rot_matr(double x){
    vector < vector < double > > mtr(2, vector < double > (2, 0));
    mtr[0][0] = cos(x);
    mtr[0][1] = sin(x);
    mtr[1][0] = -sin(x);
    mtr[1][1] = cos(x);
    return Matrix(mtr);
}*/

Matrix get_rot_matr(const double &x, const Point &p/* = Point()*/) {
    Matrix mtr = get_move_matr(p);
    mtr[0][0] = cos(x);
    mtr[0][1] = sin(x);
    mtr[1][0] = -sin(x);
    mtr[1][1] = cos(x);
    mtr[2][0] -= p.x * cos(x) - p.y * sin(x);
    mtr[2][1] -= p.x * sin(x) + p.y * cos(x);
    return Matrix(mtr);
}

Matrix get_rot_matr(const Point &p, const double &x){
    return get_rot_matr(x, p);
}

Matrix get_rot_matr(const Angle &x, const Point &p/* = Point()*/){
    return get_rot_matr(x.get_as_rad(), p);
}

Matrix get_rot_matr(const Point &p, const Angle &x){
    return get_rot_matr(x.get_as_rad(), p);
}

Matrix get_hom_matr(const double &x, const Point &p/* = Point()*/){
    Matrix ans = get_move_matr(p);
    ans[0][0] = x;
    ans[1][1] = x;
    ans[2][0] -= p.x * x;
    ans[2][1] -= p.y * x;
    return ans;
}

Matrix get_hom_matr(const Point &p, const double &x){
    return get_hom_matr(x, p);
}

Point apply_transformation(const Point &p, const Matrix &m){
    vector < double > tmp(3, 1);
    tmp[0] = p.x;
    tmp[1] = p.y;
    return (Matrix(tmp) * m).get_as_point();
}

Matrix CameraTransform(get_ide_matr(3));