#ifndef _OPENGLEVENTLISTENER
#define _OPENGLEVENTLISTENER

void recalcTimes();

void changeSize(int w, int h);

void every_frame();

void pressNormalKeys(unsigned char key, int xx, int yy);

void releaseNormalKeys(unsigned char key, int xx, int yy);

void pressKey(int key, int xx, int yy);
void releaseKey(int key, int xx, int yy);

void mouseMove(int x, int y);

void mouseButton(int button, int state, int x, int y);

void display();

void focusFunc(int state);

#endif