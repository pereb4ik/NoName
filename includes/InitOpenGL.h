#include "includes.h"

double first_time = 0, global_time = 0, last_time = 0, delta_time = 0, mousex = 0, mousey = 0;
bool mouseLeft = false, mouseRight = false, mouseWheel = false;
set < string > keysPressed;

void changeSize(int w, int h);

void every_frame(void);

void pressNormalKeys(unsigned char key, int xx, int yy);
void releaseNormalKeys(unsigned char key, int xx, int yy);

void pressKey(int key, int xx, int yy);
void releaseKey(int key, int xx, int yy);

void mouseMove(int x, int y);

void mouseButton(int button, int state, int x, int y);

void main_draw(void);

void initWindow(int *argc, char **argv){
    first_time = (double)clock() / CLOCKS_PER_SEC;
    last_time = first_time;
    glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("NoGame");
}

void funcRegistration(){
    glutDisplayFunc(main_draw);
	glutReshapeFunc(changeSize);
    glutIdleFunc(every_frame);
 
	glutIgnoreKeyRepeat(1);

	glutKeyboardFunc(pressNormalKeys);
    glutKeyboardUpFunc(releaseNormalKeys);

	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
}