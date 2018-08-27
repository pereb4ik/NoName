#include "Objects\MyObject.h"

Point cur;

void add_gl_point(const Point &a, const Color &fillColor = Color()){
    //glColor3f(fillColor.r / 255.f, fillColor.g / 255.f, fillColor.b / 255.f);
    //glVertex3f((float)to_gl_coords(a).x, (float)to_gl_coords(a).y, 0.f);
    glVertex2f((float)to_gl_coords(a).x, (float)to_gl_coords(a).y);
}

void add_gl_color(const Color &c){
    glColor4f(c.r / 255, c.g / 255, c.b / 255, c.a / 255);
}

void Segment :: draw(const Color &c){
    glLineWidth(2.5); 
    //glColor3f(1.0, 0.0, 0.0);
    add_gl_color(c);
    glBegin(GL_LINES);
    add_gl_point(this->getb());
    add_gl_point(this->gete());
    glEnd();
    /*sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(getb().x - Camera.get_abs_pos().x, HEIGHT - getb().y - Camera.get_abs_pos().y)),
        sf::Vertex(sf::Vector2f(gete().x - Camera.get_abs_pos().x, HEIGHT - gete().y - Camera.get_abs_pos().y))
    };

    window.draw(line, 2, sf::Lines);*/
}

void draw_triangle(const Point &a, const Point &b, const Point &c, const Color &fillColor = Color()){
    glBegin(GL_TRIANGLES);
    /*glVertex3f((float)to_gl_coords(a).x, (float)to_gl_coords(a).y, 0.f);
    glVertex3f((float)to_gl_coords(b).x, (float)to_gl_coords(b).y, 0.f);
    glVertex3f((float)to_gl_coords(c).x, (float)to_gl_coords(c).y, 0.f);*/
    add_gl_color(fillColor);
    add_gl_point(a);
    add_gl_point(b);
    add_gl_point(c);
    glEnd();
}

void MyPolygon :: draw(const Color &fill_color, const double &thickness = 0, const Color &outline_color = Color()){
    this->triangulate();
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < this->triangulation.size(); i++){
        //this->triangulation[i].draw(fill_color);
        draw_triangle(
            this->triangulation[i].geta(),
            this->triangulation[i].getb(),
            this->triangulation[i].getc(),
            fill_color
        );
    }
    glEnd();
    /*glBegin(GL_POLYGON);
    for (int i = 0; i < this->size(); i++){
        glVertex3f((float)(this->get(i).x / WIDTH * 2 - 1), (float)(this->get(i).y / HEIGHT * 2 - 1), 0.0f);
    }
    glEnd();*/
}

void Triangle :: draw(const Color &fillColor){
    /*glBegin(GL_TRIANGLES);
    glVertex3f((float)to_gl_coords(geta()).x, (float)to_gl_coords(geta()).y, 0.f);
    glVertex3f((float)to_gl_coords(getb()).x, (float)to_gl_coords(getb()).y, 0.f);
    glVertex3f((float)to_gl_coords(getc()).x, (float)to_gl_coords(getc()).y, 0.f);
    glEnd();*/
    draw_triangle(*a, *b, *c);
    /*
        a -= mi;
        b -= mi;
        c -= mi;
        a /= ma - mi;
        b /= ma - mi;
        c /= ma - mi;
    */

    /*sh->setUniform("texture", sf::Shader::CurrentTexture);
    sh->setUniform("a", Glsl::Vec2(geta().x / WIDTH, 1 - geta().y / HEIGHT));
    sh->setUniform("b", Glsl::Vec2(getb().x / WIDTH, 1 - getb().y / HEIGHT));
    sh->setUniform("c", Glsl::Vec2(getc().x / WIDTH, 1 - getc().y / HEIGHT));
    sh->setUniform("fillColor", Glsl::Vec4(fillColor));*/
    //sh.setParameter("W", (float)(ma.x - mi.x));                                       
    //sh.setParameter("H", (float)(ma.y - mi.y));                                       
    //sh.setUniform("pixel_threshold", (float)(500) / 30);                              
    //ma.y - mi.y));                                                                    
    /*
    a *= ma - mi;
    b *= ma - mi;
    c *= ma - mi;
    a += mi;
    b += mi;
    c += mi;
    */
    //win.draw(screen, sh);
}