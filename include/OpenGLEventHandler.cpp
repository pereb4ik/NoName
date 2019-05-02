#include "StandartIncludes.h"
#include "MyPoint.h"
#include "OpenGLEventHandler.h"

/*void do_pause(int stat){
    if (stat == PAUSE && !pause){
        cout << "UNFOCUS\n";
        pause_begin_time = clock() / CLOCKS_PER_SEC;
        pause = true;
    } else if (stat == UNPAUSE && pause){
        cout << "FOCUS\n";
        first_time += ((clock() / CLOCKS_PER_SEC) - pause_begin_time);
        last_time += ((clock() / CLOCKS_PER_SEC) - pause_begin_time);
        pause = false;
    }
}*/

void recalcTimes(){
    global_time = ((double)clock() / CLOCKS_PER_SEC) - first_time;
    delta_time = ((double)clock() / CLOCKS_PER_SEC) - last_time;
    last_time = ((double)clock() / CLOCKS_PER_SEC);
}

void changeSize(int w, int h) {
    WIDTH = w;
    HEIGHT = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    every_frame();
}

void specalKeysCheck(){
    if ((glutGetModifiers() & GLUT_ACTIVE_ALT) != 0){
        keysPressed.insert("alt");
    } else {
        keysPressed.erase ("alt");
    }
    if ((glutGetModifiers() & GLUT_ACTIVE_CTRL) != 0){
        keysPressed.insert("ctrl");
    } else {
        keysPressed.erase ("ctrl");
    }
    if ((glutGetModifiers() & GLUT_ACTIVE_SHIFT) != 0){
        keysPressed.insert("shift");
    } else {
        keysPressed.erase ("shift");
    }
}

vector < string > normalKeysConverter(unsigned char key){
    vector < string > ans;
    if (1 <= key && key <= 26){
        ans.push_back(string(1, char(key - 1 + 'a')));
        return ans;
    }
    if (('a' <= key && key <= 'z') || ('A' <= key && key <= 'Z') || ('0' <= key && key <= '9')){
        if (('A' <= key && key <= 'Z')){
            ans.push_back(string(1, char(key - 'A' + 'a')));
        }
        ans.push_back(string(1, key));
        return ans;
    }
    if (key == 8){
        ans.push_back("backspace");
        return ans;
    }
    if (key == 9){
        ans.push_back("tab");
        return ans;
    }
    if (key == 13){
        ans.push_back("enter");
        return ans;
    }
    if (key == 27){
        ans.push_back("esc");
        return ans;
    }
    if (key == 32){
        ans.push_back("space");
        return ans;
    }
    if (key == 127){
        ans.push_back("del");
        return ans;
    }
    ans.push_back(string(1, key));
    if (key == '{'){
        ans.push_back(string(1, '['));
    }
    if (key == '}'){
        ans.push_back(string(1, ']'));
    }
    return ans;
}

void pressNormalKeys(unsigned char key, int xx, int yy) { 	
    // debug_output
    cout << "Press : " << (int)key << "\n";
    // debug_output

    specalKeysCheck();

    vector < string > keys = normalKeysConverter(key);
    for (int i = 0; i < keys.size(); i++){
        keysPressed.insert(keys[i]);
    }
}

void releaseNormalKeys(unsigned char key, int xx, int yy) {
    // debug_output
    cout << "Release : " << (int)key << "\n";
    // debug_output

    specalKeysCheck();

    vector < string > keys = normalKeysConverter(key);
    for (int i = 0; i < keys.size(); i++){
        keysPressed.erase(keys[i]);
    }
}

string specialKeysConverter(int key){
    if (1 <= key && key <= 9){
        return "F" + string(1, char(key + '0'));
    }
    if (10 <= key && key <= 12){
        return "F1" + string(1, char(key - 10 + '0'));
    }
    if (key == 100){
        return "leftarrow";
    }
    if (key == 101){
        return "uparrow";
    }
    if (key == 102){
        return "rightarrow";
    }
    if (key == 103){
        return "downarrow";
    }
    if (key == 104){
        return "pageup";
    }
    if (key == 105){
        return "pagedown";
    }
    if (key == 106){
        return "home";
    }
    if (key == 107){
        return "end";
    }
    return "noone";
}

void pressKey(int key, int xx, int yy) {
    // debug_output
    cout << "Press : " << key << "\n";
    // debug_output

    specalKeysCheck();

    if (specialKeysConverter(key) != "noone"){
        keysPressed.insert(specialKeysConverter(key));
    }
}

void releaseKey(int key, int xx, int yy) {
    // debug_output
    cout << "Release : " << key << "\n";
    // debug_output

    specalKeysCheck();

    keysPressed.erase(specialKeysConverter(key));
}

void mouseMove(int x, int y) {
    cur += Point(x, HEIGHT - y) - Point(WIDTH / 2, HEIGHT / 2);
    cur.x = min(cur.x, WIDTH * 1.);
    cur.y = min(cur.y, HEIGHT * 1.);
    cur.x = max(cur.x, 0.);
    cur.y = max(cur.y, 0.);
    glutWarpPointer(WIDTH / 2, HEIGHT / 2);
    every_frame();
}

void mouseButton(int button, int state, int x, int y) {
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        mouseLeft = state != GLUT_UP;
    }
    if (button == GLUT_RIGHT_BUTTON) {
        mouseRight = state != GLUT_UP;
    }
    if (button == GLUT_MIDDLE_BUTTON) {
        mouseWheel = state != GLUT_UP;
    }
}

/*void focusFunc(int state){
    if (state == GLUT_LEFT){
        cout << "UNFOCUSED\n";
        do_pause(PAUSE);
        return;
    } else {
        cout << "FOCUSED\n";
        do_pause(UNPAUSE);
        return;
    }
}*/