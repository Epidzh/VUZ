#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include <iostream>

struct Coord {
    GLfloat x, y, z, texX, texY;
    Coord(GLfloat xc, GLfloat yc, GLfloat zc) {x = xc; y = yc; z = zc; texX = 0; texY = 0;}
    Coord(GLfloat xc, GLfloat yc, GLfloat zc, GLfloat tx, GLfloat ty) {x = xc; y = yc; z = zc; texX = tx; texY = ty;}
    Coord(GLfloat xc, GLfloat yc) {x = xc; y = yc; z = 0; texX = 0; texY = 0;}
};

std::vector<Coord> textureCoords = {
    Coord(0.0, 0.0),
    Coord(0.0, 1.0),
    Coord(1.0, 0.0),
    Coord(1.0, 1.0)
};

GLuint texture;
double angle = 0;
GLfloat camera_x = 2.82843 * cos(angle);
GLfloat camera_y = 0.70711 * sin(angle);
GLfloat camera_z = 20.0f;
GLfloat translate[] = {1.0, 1.0, 5.0};
GLdouble cube_p[][3] =
{
    {5.0, 0.0, 0},
    {0.0, 4.0, 0},
    {-3.0, 0.0, 0},
    {0.0, -2.0, 0},
};
GLfloat cube_c[][3] =
{
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 0},
};


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 0.1, 1000);
    glShadeModel(GL_SMOOTH);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrchannels;
    unsigned char* data = stbi_load("kirpitch.JPG", &width, &height, &nrchannels, 0);
    if (data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else
        std::cout << "Failed to load texture!" << std::endl;
    stbi_image_free(data);
}

void camera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(29.74707, 0, 0, 1);
    gluLookAt(camera_x, camera_y, camera_z, 0, 0, 0, 0, 1, 0);
}

void light()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_direction[] = {0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    int i = 0;
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for (i = 0; i < 4; i++){
//        GLfloat material[] = {cube_c[i][0], cube_c[i][1], cube_c[i][2], 0.0};
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        glTexCoord2d(textureCoords[i].x, textureCoords[i].y);
        glVertex3f(cube_p[i][0], cube_p[i][1], cube_p[i][2]);
    }
    GLfloat normX = (cube_p[i][1] * cube_p[(i+1)%4][2]) - (cube_p[i][2] * cube_p[(i+1)%4][1]);
    GLfloat normY = (cube_p[i][2] * cube_p[(i+1)%4][0]) - (cube_p[i][0] * cube_p[(i+1)%4][2]);
    GLfloat normZ = (cube_p[i][0] * cube_p[(i+1)%4][1]) - (cube_p[i][1] * cube_p[(i+1)%4][2]);
    glNormal3f(normX, normY, normZ);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPushMatrix();
    glTranslated(translate[0], translate[1], translate[2]);
    
    i = 0;
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for (i = 0; i < 4; i++)
    {
//        GLfloat material[] = {cube_c[i][0], cube_c[i][1], cube_c[i][2], 0.0};
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        glTexCoord2d(textureCoords[i].x, textureCoords[i].y);
        glVertex3f(cube_p[i][0], cube_p[i][1], cube_p[i][2]);
    }
    normX = (cube_p[i][1] * cube_p[(i+1)%4][2]) - (cube_p[i][2] * cube_p[(i+1)%4][1]);
    normY = (cube_p[i][2] * cube_p[(i+1)%4][0]) - (cube_p[i][0] * cube_p[(i+1)%4][2]);
    normZ = (cube_p[i][0] * cube_p[(i+1)%4][1]) - (cube_p[i][1] * cube_p[(i+1)%4][2]);
    glNormal3f(-normX, -normY, -normZ);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
//        GLfloat material[] = {cube_c[i][0], cube_c[i][1], cube_c[i][2], 0.1};
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        
        GLfloat x1 = cube_p[i][0];
        GLfloat x2 = cube_p[(i+1) % 4][0];
        GLfloat x3 = cube_p[i][0] + translate[0];
        GLfloat y1 = cube_p[i][1];
        GLfloat y2 = cube_p[(i+1) % 4][1];
        GLfloat y3 = cube_p[i][1] + translate[1];
        GLfloat z1 = cube_p[i][2];
        GLfloat z2 = cube_p[(i+1) % 4][2];
        GLfloat z3 = cube_p[i][2] + translate[2];
        normX = (y1 - y2)*(z1 - z3) - (z1 - z2)*(y1 - y3);
        normY = (z1 - z2)*(x1 - x3) - (x1 - x2)*(z1 - z3);
        normZ = (x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3);
        
//        glColor3d(cube_c[i][0], cube_c[i][1], cube_c[i][2]);
        glTexCoord2d(0,0);
        glVertex3f(cube_p[i][0], cube_p[i][1], cube_p[i][2]);
        glTexCoord2d(1,0);
        glVertex3f(cube_p[(i + 1) % 4][0], cube_p[(i + 1) % 4][1], cube_p[(i + 1) % 4][2]);
        glTexCoord2d(0,1);
        glVertex3f(cube_p[(i + 1) % 4][0] + translate[0], cube_p[(i + 1) % 4][1] + translate[1], cube_p[(i + 1) % 4][2] + translate[2]);
        glTexCoord2d(1,1);
        glVertex3f(cube_p[i][0] + translate[0], cube_p[i][1] + translate[1], cube_p[i][2] + translate[2]);
        glNormal3f(-normX, -normY, -normZ);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    if (height == 0) height = 1;
    float ratio = width / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(130, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    light();
}

void timerFunc(int value)
{
    angle += 0.1f;
    camera_x = 2.82843*cos(angle);
    camera_y = 0.70711*sin(angle);
    glutPostRedisplay();
    camera();
    light();
    glutTimerFunc(40, timerFunc, value);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300,300);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Задание 3");
    init();
    camera();
    light();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(40, timerFunc, 0);
    glutMainLoop();
}
