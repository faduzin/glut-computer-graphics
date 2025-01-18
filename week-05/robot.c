//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

int posx0 = 300, posy0 = 300, raio = 13;
float escx = 0.5, escy = 0.5;
float tx = 0.0, ty = 0.0;
float pol1 = 60.0, pol2 = 15.0;
float R = 1.0, G = 0.0, B = 0.0;
int control = 0, count = 0;

float convertex(int x){
  return (((float)x/600)*2)-1;
}

float convertey(int y){
  return 1-(((float)y/600)*2);
}

void ponto(int x, int y){
    glBegin(GL_POINTS);
        glVertex2f(convertex(x+posx0), convertey(y+posy0));
        glVertex2f(convertex(-x+posx0), convertey(y+posy0));
        glVertex2f(convertex(x+posx0), convertey(-y+posy0));
        glVertex2f(convertex(-x+posx0), convertey(-y+posy0));
        glVertex2f(convertex(y+posx0), convertey(x+posy0));
        glVertex2f(convertex(-y+posx0), convertey(x+posy0));
        glVertex2f(convertex(y+posx0), convertey(-x+posy0));
        glVertex2f(convertex(-y+posx0), convertey(-x+posy0));
    glEnd();
}

void linha(int x0, int y0, int x1, int y1){
    glBegin(GL_POLYGON);
        glVertex2f(convertex(x0-raio/5), convertey(y0));
        glVertex2f(convertex(x0+raio/5), convertey(y0));
        glVertex2f(convertex(x1+raio/5), convertey(y1));
        glVertex2f(convertex(x1-raio/5), convertey(y1));
    glEnd();
}

void circulo(int raio1){
    int par1 = 0, par2 = 0, pk = 0;
    int px = 0, py = 0, i, j;
    py = raio1;
    ponto(0, py);
    pk = 1 - raio1;
    j=py;

    for(i=0; i<j; i++){
        par1 = (2*px) + 2;
        par2 = (2*py) - 2;
        if(pk>0){
            pk += par1 + 1 - par2;
            py--;
        }else{
            pk += par1 + 1;
        }
        px++;
        ponto(px, py);
        j=py;
    }
}

void quadrilatero(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3){
    glBegin(GL_POLYGON);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

void circulopren(int incr){
    int i;
    for(i=raio+incr; i>0; i--){
        circulo(i);
    }
}

void desenha(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);

    glPushMatrix();

    glColor3f(0.1, 0.3, 0.6);  //fundo ceu
    quadrilatero(1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0, 1.0);

    glScalef(1.0, escy, 0.0);

    glColor3f(0.2, 0.5, 0.4);  //fundo chao
    quadrilatero(1.0, -0.3, 1.0, -5.0, -1.0, -5.0, -1.0, -0.3);

    glPopMatrix();
    glPushMatrix();

    glScalef(escx, escy, 0.0);
    glTranslatef(tx, ty, 0.0);

    glPushMatrix();

    glColor3f(0.3, 0.3, 0.3); //braço dir
    glTranslatef(0.32, 0.35, 0.0);
    glRotatef(pol1, 0.0, 0.0, 1.0);
    quadrilatero(0.1, 0.1, 0.1, -0.4, -0.1, -0.4, -0.1, 0.1);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-0.32, 0.35, 0.0); //braço esq
    glRotatef(-pol1, 0.0, 0.0, 1.0);
    quadrilatero(0.1, 0.1, 0.1, -0.4, -0.1, -0.4, -0.1, 0.1);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.22, -0.37, 0.0); //perna dir
    glRotatef(pol2, 0.0, 0.0, 1.0);
    quadrilatero(0.1, 0.1, 0.1, -0.6, -0.1, -0.6, -0.1, 0.1);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-0.22, -0.37, 0.0); //perna esq
    glRotatef(-pol2, 0.0, 0.0, 1.0);
    quadrilatero(0.1, 0.1, 0.1, -0.6, -0.1, -0.6, -0.1, 0.1);

    glPopMatrix();

    glColor3f(0.3, 0.3, 0.3);
    quadrilatero(0.3, 0.5, 0.3, -0.4, -0.3, -0.4, -0.3, 0.5); //torso
    glColor3f(0.2, 0.2, 0.2);
    quadrilatero(0.25, 0.45, 0.25, -0.35, -0.25, -0.35, -0.25, 0.45);

    glTranslatef(0.0, 0.7, 0.0);

    glColor3f(0.3, 0.3, 0.3);
    circulopren(50);

    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.09, 0.05, 0.0);
    circulopren(0);
    glColor3f(0.0, 0.0, 0.0);
    circulopren(-6);

    glPopMatrix();
    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-0.09, 0.05, 0.0);
    circulopren(0);
    glColor3f(0.0, 0.0, 0.0);
    circulopren(-6);

    glPopMatrix();

    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(0.0, -0.08, 0.0);
    quadrilatero(0.06, 0.01, 0.06, -0.01, -0.06, -0.01, -0.06, 0.01);

    glPopMatrix();
    glFlush();
}

void mouse(int botao, int estado, int x, int y){
    switch(botao) {
        case GLUT_LEFT_BUTTON:
            if(estado==GLUT_DOWN){
                if(count%2==0){
                    pol1 = 145.0;
                    pol2 = 60.0;
                    ty+=0.5;
                    count++;
                }else{
                    pol1 = 60.0;
                    pol2 = 15.0;
                    ty-=0.5;
                    count++;
                }
            break;
        default:
            break;
    }
    glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case '0': if(control==0){R = 0.0; G = 0.0; B = 1.0;}else{}break;
        case '1': if(control==0){R = 1.0; G = 0.0; B = 0.0;}else{escx = 0.5, escy = 0.5;} break;
        case '2': if(control==0){R = 1.0; G = 1.0; B = 0.0;}else{escx = 0.7, escy = 0.7;} break;
        case '3': if(control==0){R = 1.0; G = 1.0; B = 1.0;}else{escx = 0.9, escy = 0.9;} break;
        case '4': if(control==0){R = 0.0; G = 1.0; B = 0.0;}else{escx = 1.1, escy = 1.1;} break;
        case '5': if(control==0){R = 1.0; G = 0.0; B = 1.0;}else{escx = 1.3, escy = 1.3;} break;
        case '6': if(control==0){R = 0.5; G = 0.5; B = 0.5;}else{escx = 1.5, escy = 1.5;} break;
        case '7': if(control==0){R = 0.5; G = 1.0; B = 0.0;}else{escx = 1.6, escy = 1.6;} break;
        case '8': if(control==0){R = 0.5; G = 0.0; B = 0.5;}else{escx = 1.7, escy = 1.7;} break;
        case '9': if(control==0){R = 0.8; G = 0.3; B = 0.6;}else{escx = 2.0, escy = 2.0;} break;
        case 'e':
        case 'E': control = 1; break;
        case 'k':
        case 'K': control = 0; break;
    }
    glutPostRedisplay();
}

void tecladoEspecial(int tecla, int x, int y){
    switch (tecla) {
        case GLUT_KEY_RIGHT:
            tx+=0.05;
            break;
        case GLUT_KEY_LEFT:
            tx-=0.05;
            break;
        case GLUT_KEY_UP:
            ty+=0.05;
            break;
        case GLUT_KEY_DOWN:
            ty-=0.05;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main (int argc, char * argv [] ){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Robo");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(tecladoEspecial);
    glutMainLoop();
    return 0;
}