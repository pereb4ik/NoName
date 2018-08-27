#include "includes/Objects/objects.h"

// every frame
void every_frame(void) { 

    recalcTimes();
    
    //cout << "FPS : " << 1 / delta_time << "\n";

    // every_frame
    for (int i = 0; i < objs->size(); i++){
        (*objs)[i]->every_frame();
    }
    // every_frame

    // apply_acceleration
    for (int i = 0; i < objs->size(); i++){
        if (!(*objs)[i]->is_static){
            (*objs)[i]->apply_acceleration(delta_time);
        }
    }
    // apply_acceleration

    // apply_speed
    for (int i = 0; i < objs->size(); i++){
        (*objs)[i]->apply_speed(delta_time);
    }
    // apply_speed

    main_draw();
}

void main_draw(){
    glClearColor(0, 0, 0, 255);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < objs->size(); i++){
        if ((*objs)[i]->need_draw){
            (*objs)[i]->draw();
        }
    }

    glutSwapBuffers();
}

void add_pol(){
    MyPolygon pol;
    pol.add_vert(Point(600, 300));
    pol.add_vert(Point(610, 410));
    pol.add_vert(Point(320, 340));
    pol.add_vert(Point(260, 300));
    pol.add_vert(Point(500, 250));
    for (int i = 0; i < pol.triangulation.size(); i++){
        cout << pol.triangulation[i] << "\n";
        cout << pol.triangulation[i].mi << "\n";
        cout << pol.triangulation[i].ma << "\n";
        cout << "\n";
    }
}

void add_player(){
    Player *player = new Player("player");
    player->is_static = false;
}

void add_wall(){
    Wall *wall = new Wall("wall");
    wall->colision_mask.add(MyPolygon());
    wall->colision_mask.pols.back().add_vert(Point(0, 50));
    wall->colision_mask.pols.back().add_vert(Point(1000, 50));
    wall->colision_mask.pols.back().add_vert(Point(1000, -50));
    wall->colision_mask.pols.back().add_vert(Point(0, -50));
}

void add_objects(){
    add_pol();
    add_player();
    add_wall();
}

void debug_output(){
    get_obj("player")->write_debug_information();

    cout << objs->size() << "\n";
    for (int i = 0; i < objs->size(); i++){
        cout << (*objs)[i]->type << "\n";
    }
}

void set_scene_settings(){
    Camera.need_draw = false;
    origin->need_draw = false;
    colision_types["Player"]["Wall"] = "block";
    colision_types["Wall"]["Player"] = "block";
}

int main(int argc, char **argv) {

    initWindow(&argc, argv);

    funcRegistration();


    set_scene_settings();

    add_objects();

    debug_output();

    glutMainLoop();

    return 1;
}