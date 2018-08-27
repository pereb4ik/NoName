#include <iostream>
#include <set>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <GL/glut.h>
#include <ctime>
 
using namespace std;

#pragma warning(disable : 4996)

#define WIDTH 1000
#define HEIGHT 600

const double PI = atan(1) * 4;
const double EPS = 1e-4;
const double inf = 1e9;

map < string, map < string, string > > colision_types;
const double g = 500;