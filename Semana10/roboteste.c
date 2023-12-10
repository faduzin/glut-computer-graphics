#include <GL/glut.h>
#include <math.h>

void desenhaCubo(float scaleX, float scaleY, float scaleZ) {
    float normais[6][3] = {{0, 0, 1}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}};
    float vertices[][3] = {{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5},
                           {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}};
    int faces[][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {0, 3, 7, 4},
                      {1, 2, 6, 5}, {0, 1, 5, 4}, {2, 3, 7, 6}};

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        glNormal3fv(normais[i]);
        for (int j = 0; j < 4; j++) {
            glVertex3f(vertices[faces[i][j]][0] * scaleX,
                       vertices[faces[i][j]][1] * scaleY,
                       vertices[faces[i][j]][2] * scaleZ);
        }
    }
    glEnd();
}

void desenhaCabeca() {
    glColor3f(1.0, 0.0, 0.0);
    desenhaCubo(0.8, 0.8, 0.8);
}

void desenhaTorso() {
    glColor3f(0.0, 1.0, 0.0);
    desenhaCubo(1.0, 1.5, 0.6);
}

void desenhaBraco() {
    glColor3f(0.0, 0.0, 1.0);
    desenhaCubo(0.4, 1.2, 0.4);
}

void desenhaAntebraco() {
    glColor3f(1.0, 1.0, 0.0);
    desenhaCubo(0.4, 1.0, 0.4);
}

void desenhaPerna() {
    glColor3f(0.0, 1.0, 1.0);
    desenhaCubo(0.6, 1.5, 0.6);
}

void desenhaJoelho() {
    glColor3f(1.0, 0.0, 1.0);
    desenhaCubo(0.6, 0.6, 0.6);
}

void desenhaPanturrilha() {
    glColor3f(0.5, 0.5, 0.5);
    desenhaCubo(0.6, 1.2, 0.6);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    desenhaCabeca();
    desenhaTorso();

    glPushMatrix();
    glTranslatef(-1.2, 0.0, 0.0);
    desenhaBraco();
    glTranslatef(0.0, -1.2, 0.0);
    desenhaAntebraco();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.0, 0.0);
    desenhaBraco();
    glTranslatef(0.0, -1.2, 0.0);
    desenhaAntebraco();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, -2.0, 0.0);
    desenhaPerna();
    glTranslatef(0.0, -1.5, 0.0);
    desenhaJoelho();
    glTranslatef(0.0, -0.8, 0.0);
    desenhaPanturrilha();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, -2.0, 0.0);
    desenhaPerna();
    glTranslatef(0.0, -1.5, 0.0);
    desenhaJoelho();
    glTranslatef(0.0, -0.8, 0.0);
    desenhaPanturrilha();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Modelo do Robô");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
