#include "include/includes.h"

void display(){
    glClearColor(255, 255, 255, 255);
    glClear(GL_COLOR_BUFFER_BIT);

    globalDrawingSegmentVector.clear();

    for (map < string, Object* > :: iterator it = Object :: obj.begin(); it != Object :: obj.end(); it++){
        it->second->draw();
    }


    glPointSize(10);
    glBegin(GL_POINTS);
    add_gl_point(scrLB + scrx * WIDTH / 2 + scry * HEIGHT / 2);
    glEnd();

    drawSegments(scrLB + scrx * WIDTH / 2 + scry * HEIGHT / 2);    

    glutSwapBuffers();
}

void every_frame(){

    if (keysPressed.count("esc") || keysPressed.count("F1")){
        exit(0);
    }

    recalcTimes();
    
    for (map < string, Object* > :: iterator it = Object :: obj.begin(); it != Object :: obj.end(); it++){
        it->second->every_frame();
    }

    if (keysPressed.count("a")){
        scrLB += scrx * -delta_time * scrollSpeed;
    }

    if (keysPressed.count("d")){
        scrLB += scrx * delta_time * scrollSpeed;
    }

    if (keysPressed.count("w")){
        scrLB += scrx.ort() * delta_time * scrollSpeed;
    }

    if (keysPressed.count("s")){
        scrLB += scrx.ort() * -delta_time * scrollSpeed;
    }

    /*if (keysPressed.count("q")){
        scrLB = apply_transformation(scrLB, get_rot_matr(scrTurnSpeed * delta_time, getScrCenter()));
        scrx = scrx.rot(scrTurnSpeed * delta_time);
        scry = scry.rot(scrTurnSpeed * delta_time);
    }

    if (keysPressed.count("e")){
        scrLB = apply_transformation(scrLB, get_rot_matr(scrTurnSpeed * -delta_time, getScrCenter()));
        scrx = scrx.rot(scrTurnSpeed * -delta_time);
        scry = scry.rot(scrTurnSpeed * -delta_time);
    }*/

    /*if (mouseLeft){
        Point tmp_center = scrLB + scry * HEIGHT / 2 + scrx * WIDTH / 2;
        scry = scrx * (cur / cur.len()).x + scrx.ort() * (cur / cur.len()).y;
        scrLB = tmp_center - (scry * HEIGHT / 2 + scrx * WIDTH / 2);
    }*/

    display();
}

void cursor_constructor(){
    Cursor *cursor = new Cursor("cursor");
}

void another_triangle_construtor(){
   RotatingTriangle *rotating_triangle = new RotatingTriangle("rotating_triangle");
}

void add_triangle(){
    RisingTriangle *trang = new RisingTriangle("trang");
}

void add_arrow(){
    Arrow *arrow = new Arrow("arrow");
}

void add_loaded_polygon(){
    LoadedPolygon *pol = new LoadedPolygon("loadedPolygon");
    //pol->loadFromFile("Polygons/PolygonDataFile.polygon");
}

void pre_settings(){
    add_triangle();
    cursor_constructor();
    another_triangle_construtor();
    //add_arrow();
    add_loaded_polygon();

}

int main(int argc, char **argv) {

    pre_settings();

    initWindow(&argc, argv);

    funcRegistration();

    glutMainLoop();
}
