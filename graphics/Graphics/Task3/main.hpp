#ifndef main_h
#define main_h

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>

struct Coord {
    GLfloat x, y, z, texX, texY;
    Coord(GLfloat xc, GLfloat yc, GLfloat zc) {x = xc; y = yc; z = zc; texX = 0; texY = 0;}
    Coord(GLfloat xc, GLfloat yc, GLfloat zc, GLfloat tx, GLfloat ty) {x = xc; y = yc; z = zc; texX = tx; texY = ty;}
    Coord(GLfloat xc, GLfloat yc) {x = xc; y = yc; z = 0; texX = 0; texY = 0;}
};

float alpha = 0;
GLuint texture;
Coord cameraPosition = Coord(2.28825 * cos(alpha), 0.87403 * sin(3*alpha), 8.0);
Coord translate = Coord(1.0, 1.0, 3.0);
std::vector<Coord> points = {
    Coord(3.0, 0.0, 0),
    Coord(0.0, 3.0, 0),
    Coord(-3.0, 0.0, 0),
    Coord(-1.0, -3.0, 0),
    Coord(1.0, -3.0, 0)
};

std::vector<Coord> textureCoords = {
    Coord(0.0, 0.0),
    Coord(0.0, 1.0),
    Coord(1.0, 0.0),
    Coord(1.0, 1.0)
};

GLfloat colors[][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 0},
    {1, 0, 1}
};

#endif
