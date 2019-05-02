#ifndef _STANDART_INCLUDES_H
#define _STANDART_INCLUDES_H

#include <iostream>

#include <vector>

#include <string>
#include <cstring>

#include <set>

#include <map>

#include <cmath>

#include <algorithm>

#include <ctime>

//#define _WCHAR_T_DEFINED
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
	#include <GL/glut.h>
#endif

#if defined(__APPLE__)
	#include <GLUT/glut.h>
#endif


using namespace std;

extern int WIDTH, HEIGHT;
extern double EPS, PI;


extern double first_time, global_time, last_time, delta_time, pause_begin_time;
extern bool mouseLeft, mouseRight, mouseWheel;
extern set < string > keysPressed;
extern double scrollSpeed, turnSpeed;
extern double inf;
// cur объявлен в Point.h

#endif
