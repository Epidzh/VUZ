#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

void init_view()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 0.1, 1000);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_direction[] = {1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
}


void display() {
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
        {1, 1, 1},
        {0, 1, 0},
    };

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
        GLfloat material[] = {cube_c[i][0], cube_c[i][1], cube_c[i][2], 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        glVertex3f(cube_p[i][0], cube_p[i][1], cube_p[i][2]);
    }
    glEnd();

    glutSwapBuffers();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Задание 1");
    init_view();
    glutDisplayFunc(display);
    glutMainLoop();
}
