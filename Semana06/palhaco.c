//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

float angx = 0.0;
float angy = 0.0;
float angz = 0.0;
int opcao = 0;

void init()
{
    glClearColor(0, 0, 0, 0); // Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, -10.0, 10.0);
}

void desenha(){
    init();

    glPushMatrix();

    glRotatef(angz, 0.0, 0.0, 1.0);
    glRotatef(angy, 0.0, 1.0, 0.0);
    glRotatef(angx, 1.0, 0.0, 0.0);

    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(2, 50, 50);

    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glutSolidSphere(0.3, 50, 50);

    glPopMatrix();
    glPushMatrix();
    
    glColor3f(0.1, 0.1, 0.1);
    glRotatef(40, 1.0, 0.0, 0.0);
    glRotatef(40, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glutSolidSphere(0.2, 50, 50);

    glPopMatrix();
    glPushMatrix();

    glColor3f(0.1, 0.1, 0.1);
    glRotatef(-40, 1.0, 0.0, 0.0);
    glRotatef(-40, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glutSolidSphere(0.2, 50, 50);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.0, 1.7, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.5, 0.5);
    glutSolidCone(0.8, 1.5, 50, 50);

    glPopMatrix();

    glPopMatrix();

    glFlush();
}

void teclado(unsigned char key, int x, int y){
    switch(key){
        case '1': angx+=2.0; break;
        case '2': angx-=2.0; break;
        case '3': angy+=2.0; break;
        case '4': angy-=2.0; break;
        case '5': angz+=2.0; break;
        case '6': angz-=2.0; break;
    }
    glutPostRedisplay();
}

int main (int argc, char * argv [] ){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Palhaço");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}