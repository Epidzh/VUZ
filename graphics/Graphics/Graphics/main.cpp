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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_direction[] = {1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glShadeModel(GL_SMOOTH);
}

void display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 0.1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);

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
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; i++){
        GLfloat material_diffuse[] = {colors[i][0], colors[i][1], colors[i][2], 1.0};
        glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_diffuse);
        glColor3d(colors[i][0], colors[i][1], colors[i][2]);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(points[i][0], points[i][1], points[i][2]);
        glVertex3f(points[(i + 1) % 5][0], points[(i + 1) % 5][1], points[(i + 1) % 5][2]);
    }
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    float ratio = 1.0* width / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(130, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("Задача 1");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
