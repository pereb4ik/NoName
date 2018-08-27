#include "InitOpenGL.h";

void recalcTimes(){
    global_time = ((double)clock() / CLOCKS_PER_SEC) - first_time;
    delta_time = ((double)clock() / CLOCKS_PER_SEC) - last_time;
    last_time = ((double)clock() / CLOCKS_PER_SEC);
}

void changeSize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    // предотвращение деления на ноль
    /*if (h == 0)
        h = 1;
    float ratio =  w * 1.0 / h;
    // используем матрицу проекции
    glMatrixMode(GL_PROJECTION);
    // обнуляем матрицу
    glLoadIdentity();
    // установить параметры вьюпорта
    glViewport(0, 0, w, h);
    // установить корректную перспективу
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    // вернуться к матрице проекции
    glMatrixMode(GL_MODELVIEW);*/
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
    mousex = xx;
    mousey = yy;

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
    mousex = xx;
    mousey = yy;

    vector < string > keys = normalKeysConverter(key);
    for (int i = 0; i < keys.size(); i++){
        keysPressed.erase(keys[i]);
    }
}

string specialKeysConverter(int key){
    if (1 <= key && key <= 9){
        return "F" + char(key + '0');
    }
    if (10 <= key && key <= 12){
        return "F1" + char(key - 10 + '0');
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
}

void pressKey(int key, int xx, int yy) {

    // debug_output
    cout << "Press : " << key << "\n";
    // debug_output

    specalKeysCheck();
    mousex = xx;
    mousey = yy;

    keysPressed.insert(specialKeysConverter(key));    
}

void releaseKey(int key, int xx, int yy) {

    // debug_output
    cout << "Release : " << key << "\n";
    // debug_output

    specalKeysCheck();
    mousex = xx;
    mousey = yy;

    keysPressed.erase(specialKeysConverter(key));
}

void mouseMove(int x, int y) {
    mousex = x;
    mousey = y;
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




#define COLUMNS 40
#define ROWS 40

void DrawGrid();
void reshape_callback(int w, int h){    // Инициализираме прозореца на екрана
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, COLUMNS, 0, ROWS, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
void display_callback(){
    cout << "draw";
    DrawGrid();   //Извикваме функция за изчертаване мрежа в прозореца
    glutSwapBuffers();  // Визуализиране на начертаното в буфера на екрана
}

void DrawGrid(){
    int x, y;
    glClearColor(0, 0, 0, 255); //Изчистваме екрана в черно
    glClear(GL_COLOR_BUFFER_BIT); //Изчистваме буфера за цвета
    glColor3ub(255, 255, 255); //Определяме цвета за рисуване в RGB стандарт
    glLineWidth(1); //Определяме дебелината на линията в пиксели
    glBegin(GL_LINES); // Рисуваме линии. Начало
    ///========
    for (x = 0; x < COLUMNS; x++){
        for (y = 0; y < ROWS; y++){
            {
                                
            } 
        }
    }
    glEnd(); 
}