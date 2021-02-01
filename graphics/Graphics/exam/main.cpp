#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

GLfloat alpha = 1.0f;

void init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 0.1, 1000);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void setCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
}

void setLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_direction[] = {1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLdouble points[][3] = {
        {4.0 / 4, 4.0 / 4, 0},
        {-4.0 / 4, 4.0 / 4, 0},
        {-4.0 / 4, -4.0 / 4, 0},
        {6.0 / 4, -4.0 / 4, 0},
    };

    GLfloat colors[][3] = {
        {1, 0, 0},
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 0},
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
    glTranslated(1, 1, 0);
    glRotatef(alpha, 0, 0, 1);
    int i = 0;
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < 4; i++){
        GLfloat material[] = {colors[i][0], colors[i][1], colors[i][2], 1.0};
        GLfloat normX = (points[i][1] * points[(i+1)%4][2]) - (points[i][2] * points[(i+1)%4][1]);
        GLfloat normY = (points[i][2] * points[(i+1)%4][0]) - (points[i][0] * points[(i+1)%4][2]);
        GLfloat normZ = (points[i][0] * points[(i+1)%4][1]) - (points[i][1] * points[(i+1)%4][2]);
        glNormal3f(normX, normY, normZ);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        glVertex3f(points[i][0], points[i][1], points[i][2]);
    }
    i = 0;
    glEnd();
    glPopMatrix();
    
//    линия, чтобы убедиться в "правильности вращения"
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(10, 10, 0);
    glEnd();

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
}

void timerFunc(int value) {
    alpha += 2.0f;
    glutPostRedisplay();
    setCamera();
    glutTimerFunc(40, timerFunc, value);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Вариант 21");
    init();
    setCamera();
    setLight();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(40, timerFunc, 0);
    glutMainLoop();
}
