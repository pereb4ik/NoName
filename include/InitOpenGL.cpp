//#include "MyGeometry\MyPoint.h"
#include "StandartIncludes.h"
#include "InitOpenGL.h"
#include "OpenGLEventHandler.h"

void initWindow(int *argc, char **argv){
    glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("NoGame");

    //glutSetCursor(GLUT_CURSOR_NONE);
}

void funcRegistration(){

    // frequent funcs
    glutDisplayFunc(display);
    glutIdleFunc(every_frame);
    // frequent funcs

    glutReshapeFunc(changeSize);
 
	glutIgnoreKeyRepeat(1);

    // normal keys
	glutKeyboardFunc(pressNormalKeys);
    glutKeyboardUpFunc(releaseNormalKeys);
    // normal keys

    // special keys
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    // special keys

    // mouse
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
    glutPassiveMotionFunc(mouseMove);
    // mouse

    //glutEntryFunc(focusFunc);
}