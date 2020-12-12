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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void getTextures() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("wallTex3.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        std::cout << "Success load texture!" << std::endl;
    }
    else
        std::cout << "Failed to load texture!" << std::endl;
    stbi_image_free(data);
}


void init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 0.1, 1000);
    glShadeModel(GL_SMOOTH);
    getTextures();
}

void setCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-21.6475107972, 0, 0, 1);
    gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, 0, 0, 0, 0, 1, 0);
}

void setLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_direction[] = {0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    drawBase();
    glPushMatrix();
    glTranslated(translate_coords.x, translate_coords.y, translate_coords.z);
    drawBase();
    glPopMatrix();
    drawQuads();
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
    cameraPosition.x = 2.28825 * cos(alpha);
    cameraPosition.y = 0.87403 * sin(alpha);
    glutPostRedisplay();
    setCamera();
    glutTimerFunc(40, timerFunc, value);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Задача 3");
    init();
    setCamera();
    setLight();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(40, timerFunc, 0);
    glutMainLoop();
}
