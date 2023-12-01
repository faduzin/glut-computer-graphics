//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

int posx0 = 300, posy0 = 300, raio = 13;
float escx = 0.5, escy = 0.5;
float tx = -1.3, ty = 0.25;
float theta = 0.0;
float R = 1.0, G = 0.0, B = 0.0;
int control = 0;

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

void retangulo(float x0, float y0, float x1, float y1){
    glBegin(GL_POLYGON);
        glVertex2f(-x0, y0);
        glVertex2f(x0, y0);
        glVertex2f(x1, -y1);
        glVertex2f(-x1, -y1);
    glEnd();
}

void circulopren(int incr){
    int i;
    for(i=raio+incr; i>0; i--){
        circulo(i);
    }
}

void pneu(){
    glColor3f(0.1, 0.1, 0.1);
    circulopren(8);
    glColor3f(0.6, 0.6, 0.6);
    circulopren(0);
    glColor3f(0.3, 0.3, 0.3);
    retangulo(0.04, 0.01, 0.04, 0.01);
    retangulo(0.01, 0.04, 0.01, 0.04);
}

void desenha(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);

    glPushMatrix();

    glColor3f(0.1, 0.2, 0.7);  //ceu
    retangulo(1.0, 1.0, 1.0, 0.0);

    glScalef(1.0, escy, 0.0);

    glColor3f(1.0, 0.7, 0.0);  //deserto
    retangulo(1.0, 0.5, 1.0, 3.0);

    glColor3f(0.05, 0.05, 0.05); //pista
    retangulo(1.0, 0.22, 1.0, 0.22);
    glColor3f(1.0, 0.8, 0.0);
    retangulo(1.0, 0.02, 1.0, 0.02);

    glPopMatrix();
    glPushMatrix();

    glScalef(escx, escy, 0.0);

    glPushMatrix();

    glTranslatef(-0.5, 0.4, 0.0); //cacto1
    glColor3f(0.0, 0.8, 0.1);
    retangulo(0.05, 0.3, 0.05, 0.0);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(1.1, -0.7, 0.0);  //cacto2
    retangulo(0.05, 0.3, 0.05, 0.0);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-1.2, -0.9, 0.0);  //cacto3
    retangulo(0.05, 0.3, 0.05, 0.0);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.0, -1.0, 0.0);  //cacto4
    retangulo(0.05, 0.3, 0.05, 0.0);

    glPopMatrix();
    glTranslatef(tx, ty, 0.0);

    glColor3f(0.4, 0.3, 0.8);  //onibus
    retangulo(0.4, 0.25, 0.4, 0.1);
    glColor3f(0.1, 0.2, 0.7);  //janelas
    retangulo(0.34, 0.19, 0.34, -0.05);

    glPushMatrix();

    glTranslatef(0.27, 0.12, 0.0); //janela motorista
    glColor3f(0.2, 0.6, 0.7);
    retangulo(0.07, 0.07, 0.07, 0.07);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.27, -0.1, 0.0); //pneu dianteiro
    glRotatef(theta, 0.0, 0.0, 1.0);
    pneu();

    glPopMatrix();

    glTranslatef(-0.27, -0.1, 0.0);  //pneu traseiro
    glRotatef(theta, 0.0, 0.0, 1.0);
    pneu();

    glPopMatrix();
    glFlush();
}

void mouse(int botao, int estado, int x, int y){
    switch(botao) {
        case GLUT_LEFT_BUTTON:
            if(estado==GLUT_DOWN){
                    
            break;
        default:
            break;
    }
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
            theta-=12.0;
            break;
        case GLUT_KEY_LEFT:
            tx-=0.05;
            theta+=12.0;
            break;
        case GLUT_KEY_UP:
            ty=0.25;
            break;
        case GLUT_KEY_DOWN:
            ty=-0.0;
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