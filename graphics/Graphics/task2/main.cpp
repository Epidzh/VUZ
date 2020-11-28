#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>


GLfloat camera_x = 0.0f;
GLfloat camera_y = 0.0f;
GLfloat camera_z = 5.0f;
float alpha = 0;


void init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130, 1, 0.1, 1000);
    glShadeModel(GL_SMOOTH);
}

void setCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_x, camera_y, camera_z, 0, 0, 0, 0, 1, 0);
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

    
//    glPushMatrix();
//    glRotated(45, 0, 1, 0);
//    glScaled(0.5, 0.5, 0.5);
//    glPopMatrix();
    
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
    
    glLoadIdentity();
    glTranslatef(1, 1, 1);
    
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
    glFlush();
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
    alpha += 0.1f;
    camera_x = 4*cos(alpha);
    camera_y = 2*sin(alpha);
    glutPostRedisplay();
    std::cout << alpha << ", " << camera_x << " " << camera_y << std::endl;
    glutTimerFunc(40, timerFunc, value);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Задача 2");
    init();
    setCamera();
    setLight();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(40, timerFunc, 0);
    glutMainLoop();
}

//static int year = 0, day = 0;
//
//void init(void)
//{
//   glClearColor (0.0, 0.0, 0.0, 0.0);
//   glShadeModel (GL_FLAT);
//}
//
//void display(void)
//{
//   glClear (GL_COLOR_BUFFER_BIT);
//   glColor3f (1.0, 1.0, 1.0);
//
//   glPushMatrix();
//   glutWireSphere(1.0, 20, 16);   /* draw sun */
//   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
//   glTranslatef (2.0, 0.0, 0.0);
//   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
//   glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
//   glPopMatrix();
//   glutSwapBuffers();
//}
//
//void reshape (int w, int h)
//{
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
//   glMatrixMode (GL_PROJECTION);
//   glLoadIdentity ();
//   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();
//   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//}
//
//void keyboard (unsigned char key, int x, int y)
//{
//   switch (key) {
//      case 'd':
//         day = (day + 10) % 360;
//         glutPostRedisplay();
//         break;
//      case 'D':
//         day = (day - 10) % 360;
//         glutPostRedisplay();
//         break;
//      case 'y':
//         year = (year + 5) % 360;
//         glutPostRedisplay();
//         break;
//      case 'Y':
//         year = (year - 5) % 360;
//         glutPostRedisplay();
//         break;
//      default:
//         break;
//   }
//}
//
//int main(int argc, char** argv)
//{
//   glutInit(&argc, argv);
//   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
//   glutInitWindowSize (500, 500);
//   glutInitWindowPosition (100, 100);
//   glutCreateWindow (argv[0]);
//   init ();
//   glutDisplayFunc(display);
//   glutReshapeFunc(reshape);
//   glutKeyboardFunc(keyboard);
//   glutMainLoop();
//   return 0;
//}
