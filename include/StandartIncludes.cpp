#include "StandartIncludes.h"
int WIDTH = 1000, HEIGHT = 600;
double EPS = 1e-5, PI = atan(1) * 4; 
double first_time = 0, global_time = 0, last_time = 0, delta_time = 0, pause_begin_time = 0;
bool mouseLeft = false, mouseRight = false, mouseWheel = false;
set < string > keysPressed;
double scrollSpeed = 50;
double inf = 1e9;