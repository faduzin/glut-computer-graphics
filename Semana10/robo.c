#include <GL/glut.h>
#include <math.h>

void init()
{
    glClearColor(0, 0, 0, 0); // Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-6.0, 6.0, -6.0, 6.0, -14.0, 14.0);
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    gluLookAt(7.0, 4.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 600, 600);
}

// Função para desenhar um cubo com escalas e normais
void desenhaCubo(float scaleX, float scaleY, float scaleZ) {
    // Definindo normais para cada face (perpendiculares às faces)
    float normais[6][3] = {{0, 0, 1}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}};

    // Definindo vértices do cubo
    float vertices[][3] = {{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5},
                           {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}};

    // Definindo faces do cubo
    int faces[][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {0, 3, 7, 4},
                      {1, 2, 6, 5}, {0, 1, 5, 4}, {2, 3, 7, 6}};

    // Desenhando o cubo
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

// Função para desenhar a cabeça do robô
void desenhaCabeca() {
    glColor3f(1.0, 0.0, 0.0);
    desenhaCubo(0.8, 0.8, 0.8);
}

// Função para desenhar o torso do robô
void desenhaTorso() {
    glColor3f(0.0, 1.0, 0.0);
    desenhaCubo(1.0, 1.5, 0.6);
}

// Função para desenhar um braço do robô
void desenhaBraco() {
    glColor3f(0.0, 0.0, 1.0);
    desenhaCubo(0.4, 1.2, 0.4);
}

// Função para desenhar o antebraço do robô
void desenhaAntebraco() {
    glColor3f(1.0, 1.0, 0.0);
    desenhaCubo(0.4, 1.0, 0.4);
}

// Função para desenhar uma perna do robô
void desenhaPerna() {
    glColor3f(0.0, 1.0, 1.0);
    desenhaCubo(0.6, 1.5, 0.6);
}

// Função para desenhar o joelho do robô
void desenhaJoelho() {
    glColor3f(1.0, 0.0, 1.0);
    desenhaCubo(0.6, 0.6, 0.6);
}

// Função para desenhar a panturrilha do robô
void desenhaPanturrilha() {
    glColor3f(0.5, 0.5, 0.5);
    desenhaCubo(0.6, 1.2, 0.6);
}

// Função de desenho principal
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Desenhando as partes do robô
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

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Robo");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
