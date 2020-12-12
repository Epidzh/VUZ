
void drawBase() {
    int i = 0;
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < 5; i++){
        GLfloat material[] = {colors[i][0], colors[i][1], colors[i][2], 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        glVertex3f(points[i][0], points[i][1], points[i][2]);
    }
    i = 0;
    GLfloat normX = (points[i][1] * points[(i+1)%5][2]) - (points[i][2] * points[(i+1)%5][1]);
    GLfloat normY = (points[i][2] * points[(i+1)%5][0]) - (points[i][0] * points[(i+1)%5][2]);
    GLfloat normZ = (points[i][0] * points[(i+1)%5][1]) - (points[i][1] * points[(i+1)%5][2]);
    glNormal3f(-normX, -normY, -normZ);
    glEnd();
}

void drawQuads() {
    glBegin(GL_QUADS);
    for (int i = 0; i < 5; i++){
        GLfloat material[] = {colors[i][0], colors[i][1], colors[i][2], 0.1};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        
        GLfloat x1 = points[i][0];
        GLfloat x2 = points[(i+1)%5][0];
        GLfloat x3 = points[i][0] + translate_coords[0];
        GLfloat y1 = points[i][1];
        GLfloat y2 = points[(i+1)%5][1];
        GLfloat y3 = points[i][1] + translate_coords[1];
        GLfloat z1 = points[i][2];
        GLfloat z2 = points[(i+1)%5][2];
        GLfloat z3 = points[i][2] + translate_coords[2];
        GLfloat normX = (y1 - y2)*(z1 - z3) - (z1 - z2)*(y1 - y3);
        GLfloat normY = (z1 - z2)*(x1 - x3) - (x1 - x2)*(z1 - z3);
        GLfloat normZ = (x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3);
        
        glColor3d(colors[i][0], colors[i][1], colors[i][2]);
        
        glVertex3f(points[i][0], points[i][1], points[i][2]);
        glVertex3f(points[(i + 1) % 5][0], points[(i + 1) % 5][1], points[(i + 1) % 5][2]);
        glVertex3f(points[(i + 1) % 5][0] + translate_coords[0], points[(i + 1) % 5][1] + translate_coords[1], points[(i + 1) % 5][2] + translate_coords[2]);
        glVertex3f(points[i][0] + translate_coords[0], points[i][1] + translate_coords[1], points[i][2] + translate_coords[2]);
        
        glNormal3f(normX, normY, normZ);
    }
    glEnd();
}
