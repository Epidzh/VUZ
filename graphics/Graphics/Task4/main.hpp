//
//  main.hpp
//  Graphics
//
//  Created by Сергей Петров on 07.12.2020.
//

#ifndef main_h
#define main_h

float alpha = 0;
GLfloat camera_x = 2.28825 * cos(alpha);
GLfloat camera_y = 0.87403 * sin(alpha);
GLfloat camera_z = 15.0f;

GLfloat translate_coords[] = {1.0, 1.0, 5.0};
GLdouble points[][3] = {
    {3.0, 0.0, 0},
    {0.0, 3.0, 0},
    {-3.0, 0.0, 0},
    {-1.0, -3.0, 0},
    {1.0, -3.0, 0}
};

GLfloat colors[][3] = {
    {1, 0, 0},
    {0.3, 0, 1},
    {0, 0, 1},
    {0, 1, 0},
    {1, 0.7, 0}
};

#endif /* main_h */
