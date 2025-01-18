//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

int posx0 = 0, posy0 = 0, raio = 10;
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

void circulo(){
    int par1 = 0, par2 = 0, pk = 0;
    int px = 0, py = 0, i, j;
    py = raio;
    ponto(0, py);
    pk = 1 - raio;
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

void desenha(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(R, G, B);
    glPointSize(5);
    circulo();
    glFlush();
}

void mouse(int botao, int estado, int x, int y){
    switch(botao) {
        case GLUT_LEFT_BUTTON:
            if(estado==GLUT_DOWN){
                    posx0 = x;
                    posy0 = y;
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
    glutCreateWindow("Bresenham - circulo");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}