#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>


float alpha = 0;
GLfloat camera_x = 2.28825*cos(alpha);
GLfloat camera_y = 0.87403*sin(alpha);
GLfloat camera_z = 20.0f;
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
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 0},
    {1, 0, 1}
};


void init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
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
    GLfloat light_direction[] = {1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
}

void drawTriangles() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; i++){
        GLfloat material[] = {colors[i][0], colors[i][1], colors[i][2], 1.0};
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material);
        glColor3d(colors[i][0], colors[i][1], colors[i][2]);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(points[i][0], points[i][1], points[i][2]);
        glVertex3f(points[(i + 1) % 5][0], points[(i + 1) % 5][1], points[(i + 1) % 5][2]);
    }
    glEnd();
}

void drawQuads() {
    glBegin(GL_QUADS);
    for (int i = 0; i < 5; i++){
        GLfloat material[] = {colors[i][0], colors[i][1], colors[i][2], 1.0};
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material);
        glColor3d(colors[i][0], colors[i][1], colors[i][2]);
        
        glVertex3f(points[i][0], points[i][1], points[i][2]);
        glVertex3f(points[(i + 1) % 5][0], points[(i + 1) % 5][1], points[(i + 1) % 5][2]);
        glVertex3f(points[(i + 1) % 5][0] + translate_coords[0], points[(i + 1) % 5][1] + translate_coords[1], points[(i + 1) % 5][2] + translate_coords[2]);
        glVertex3f(points[i][0] + translate_coords[0], points[i][1] + translate_coords[1], points[i][2] + translate_coords[2]);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    drawTriangles();
    glPushMatrix();
    glTranslated(translate_coords[0], translate_coords[1], translate_coords[2]);
    drawTriangles();
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
