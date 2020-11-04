#include <iostream>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif


void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {10.0f, 0.0f, 0.0f};
    GLfloat spot_direction[] = {0.0f, 0.0f, 0.0f};
//
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glShadeModel(GL_SMOOTH);
}

void display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 50, 0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glOrtho(0, 640, 0, 480, -10, 10);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glLoadIdentity();
    
    GLdouble points[][3] = {
        {3.0, 0.0, 0.0},
        {0.0, 3.0, 0.0},
        {-3.0, 0.0, 0},
        {-1.0, -3.0, 0},
        {1.0, -3.0, 0}
    };
    
    GLdouble colors[][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {1, 0, 1}
    };
    
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
    
//    for (int i = 0; i < 5; i++){
//        glColor3d(colors[i][0], colors[i][1], colors[i][2]);
//        glVertex3d(0.0, 0.0, 0.0);
//        glVertex3d(points[i][0], points[i][1], points[i][2]);
//        glVertex3d(points[(i + 1) % 5][0], points[(i + 1) % 5][1], points[(i + 1) % 5][2]);
//    }
    glColor3d(1, 0, 0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);

    glColor3d(0, 1, 0);
    glVertex3d(0.0, 0.0, 0);
    glVertex3d(0.0, 1.0, 0);
    glVertex3d(-1.0, 0.0, 0);

    glColor3d(0, 0, 1);
    glVertex3d(0.0, 0.0, 0);
    glVertex3d(-0.333, -1.0, 0);
    glVertex3d(0.333, -1.0, 0);

    glColor3d(1, 1, 0);
    glVertex3d(0.0, 0.0, 0);
    glVertex3d(-1.0, 0.0, 0);
    glVertex3d(-0.333, -1.0, 0);

    glColor3d(1, 0, 1);
    glVertex3d(0.0, 0.0, 0);
    glVertex3d(0.333, -1.0, 0);
    glVertex3d(1.0, 0.0, 0);

    glEnd();

    glutSwapBuffers();
}

int main(int argc, char * argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("First Lab");
    init();
    glutDisplayFunc(display);
//    glutReshapeFunc()
//    glutFullScreen();
    glutMainLoop();
    return 0;
}
