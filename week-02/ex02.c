//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

float posx = 0.0, posy = 0.0;
float R = 0.0, G = 0.0, B = 0.0;


float convertex(int x){
  return (((float)x/600)*2)-1;
}

float convertey(int y){
  return 1-(((float)y/600)*2);
}

void ponto(float x, float y){
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void desenha(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(R, G, B);
    glPointSize(5);
    ponto(posx, posy);
    glFlush();
}

void mouse(int botao, int estado, int x, int y){
    switch(botao) {
        case GLUT_LEFT_BUTTON:
            if(estado==GLUT_DOWN)
                posx = convertex(x);
                posy = convertey(y);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case '0': R = 1.0; G = 0.0; B = 0.0; break;
        case '1': R = 1.0; G = 1.0; B = 0.0; break;
        case '2': R = 1.0; G = 0.0; B = 1.0; break;
        case '3': R = 1.0; G = 1.0; B = 1.0; break;
        case '4': R = 0.0; G = 1.0; B = 0.0; break;
        case '5': R = 0.0; G = 0.0; B = 1.0; break;
        case '6': R = 0.0; G = 1.0; B = 1.0; break;
        case '7': R = 0.7; G = 0.0; B = 0.3; break;
        case '8': R = 0.5; G = 0.5; B = 0.5; break;
        case '9': R = 0.5; G = 0.5; B = 1.0; break;
    }
    glutPostRedisplay();
}

int main (int argc, char * argv [] ){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercicio 02");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}