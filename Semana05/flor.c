//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

int posx0 = 300, posy0 = 300, raio = 10;
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

void circulopren(int incr){
    int i;
    for(i=raio+incr; i>0; i--){
        if(i>raio-20 && incr==0){
            glColor3f(1.0, 0.1, 0.6);
        }else{
            if(incr==0){
                glColor3f(1.0, 0.1, 0.4);
            }
        }
        circulo(i);
    }
}

void desenha(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.7, 0.0);
    linha(300,300, 300, 600);
    
    glPointSize(2);

    glPushMatrix();

    glTranslatef(convertex(2*raio+posx0), 0.0, 0.0);
    circulopren(0);

    glPopMatrix();
    glPushMatrix();

    glRotatef(60, 0.0, 0.0, 1.0);
    glTranslatef(convertex(2*raio+posx0), 0.0, 0.0);
    circulopren(0);

    glPopMatrix();
    glPushMatrix();

    glRotatef(120, 0.0, 0.0, 1.0);
    glTranslatef(convertex(2*raio+posx0), 0.0, 0.0);
    circulopren(0);

    glPopMatrix();
    glPushMatrix();

    glRotatef(180, 0.0, 0.0, 1.0);
    glTranslatef(convertex(2*raio+posx0), 0.0, 0.0);
    circulopren(0);

    glPopMatrix();
    glPushMatrix();

    glRotatef(240, 0.0, 0.0, 1.0);
    glTranslatef(convertex(2*raio+posx0), 0.0, 0.0);
    circulopren(0);

    glPopMatrix();
    glPushMatrix();

    glRotatef(300, 0.0, 0.0, 1.0);
    glTranslatef(convertex(2*raio+posx0), 0.0, 0.0);
    circulopren(0);

    glPopMatrix();

    glColor3f(R, G, B);
    circulopren(raio*0.6);


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
        case '1': if(control==0){R = 1.0; G = 0.0; B = 0.0;}else{raio = 10;} break;
        case '2': if(control==0){R = 1.0; G = 1.0; B = 0.0;}else{raio = 20;} break;
        case '3': if(control==0){R = 1.0; G = 1.0; B = 1.0;}else{raio = 30;} break;
        case '4': if(control==0){R = 0.0; G = 1.0; B = 0.0;}else{raio = 40;} break;
        case '5': if(control==0){R = 1.0; G = 0.0; B = 1.0;}else{raio = 50;} break;
        case '6': if(control==0){R = 0.5; G = 0.5; B = 0.5;}else{raio = 60;} break;
        case '7': if(control==0){R = 0.5; G = 1.0; B = 0.0;}else{raio = 70;} break;
        case '8': if(control==0){R = 0.5; G = 0.0; B = 0.5;}else{raio = 80;} break;
        case '9': if(control==0){R = 0.8; G = 0.3; B = 0.6;}else{raio = 90;} break;
        case 'e':
        case 'E': control = 1; break;
        case 'k':
        case 'K': control = 0; break;
    }
    glutPostRedisplay();
}

int main (int argc, char * argv [] ){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Flor");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}