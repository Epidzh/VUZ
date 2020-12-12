
void drawBase() {
    int i;
    std::vector<Coord> texCoords;
    for (auto i : points)
        texCoords.push_back(Coord((i.x + 3) / 7, (i.y + 3) / 7));
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < 5; i++){
        GLfloat material[] = {1, 1, 1, 0.1};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        
        glTexCoord2d(texCoords[i].x, texCoords[i].y);
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }
    i = 0;
    GLfloat normX = (points[i].y * points[(i+1)%5].z) - (points[i].z * points[(i+1)%5].y);
    GLfloat normY = (points[i].z * points[(i+1)%5].x) - (points[i].x * points[(i+1)%5].z);
    GLfloat normZ = (points[i].x * points[(i+1)%5].y) - (points[i].y * points[(i+1)%5].z);
    glNormal3f(-normX, -normY, -normZ);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawQuads() {
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for (int i = 0; i < 5; i++){
//        GLfloat material[] = {colors[i][0], colors[i][1], colors[i][2], 0.1};
        GLfloat material[] = {1, 1, 1, 0.1};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
        
        GLfloat x1 = points[i].x;
        GLfloat x2 = points[(i+1)%5].x;
        GLfloat x3 = points[i].x + translate_coords.x;
        GLfloat y1 = points[i].y;
        GLfloat y2 = points[(i+1)%5].y;
        GLfloat y3 = points[i].y + translate_coords.y;
        GLfloat z1 = points[i].z;
        GLfloat z2 = points[(i+1)%5].z;
        GLfloat z3 = points[i].z + translate_coords.z;
        GLfloat normX = (y1 - y2)*(z1 - z3) - (z1 - z2)*(y1 - y3);
        GLfloat normY = (z1 - z2)*(x1 - x3) - (x1 - x2)*(z1 - z3);
        GLfloat normZ = (x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3);

        glTexCoord2d(0,0);
        glVertex3f(x1, y1, z1);
        glTexCoord2d(1,0);
        glVertex3f(x2, y2, z2);
        glTexCoord2d(0,1);
        glVertex3f(points[(i + 1) % 5].x + translate_coords.x, points[(i + 1) % 5].y + translate_coords.y, points[(i + 1) % 5].z + translate_coords.z);
        glTexCoord2d(1,1);
        glVertex3f(x3, y3, z3);
        
        glNormal3f(normX, normY, normZ);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
