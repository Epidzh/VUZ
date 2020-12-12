#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#include "main.hpp"
#include "geometry.cpp"


void init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 0.1, 1000);
    glShadeModel(GL_SMOOTH);
}

void setCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-21.6475107972, 0, 0, 1);
    gluLookAt(camera_x, camera_y, camera_z, 0, 0, 0, 0, 1, 0);
}

void setLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_direction[] = {0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    drawBase();
    glPushMatrix();
    glTranslated(translate_coords[0], translate_coords[1], translate_coords[2]);
    drawBase();
    glPopMatrix();
    drawQuads();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    float ratio = width / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(130, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    setLight();
}

void timerFunc(int value) {
    alpha += 0.1f;
    camera_x = 2.28825*cos(alpha);
    camera_y = 0.87403*sin(alpha);
    glutPostRedisplay();
    setCamera();
    glutTimerFunc(40, timerFunc, value);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Задача 2");
    init();
    setCamera();
    setLight();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(40, timerFunc, 0);
    glutMainLoop();
}
