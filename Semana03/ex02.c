//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

int posx0 = 0, posy0 = 0, posx1 = 0, posy1 = 0, posx2 = 0, posy2 = 0;
float R = 1.0, G = 0.0, B = 0.0;
int count = 0, control = 0;

float convertex(int x){
  return (((float)x/600)*2)-1;
}

float convertey(int y){
  return 1-(((float)y/600)*2);
}

void ponto(int x, int y){
    glBegin(GL_POINTS);
        glVertex2f(convertex(x), convertey(y));
    glEnd();
}

void linha(int x0, int y0, int x1, int y1){
    int dx, dy, i, par1, par2, pk, incx, incy, px=x0, py=y0;
    
    dx = fabs(x1 - x0);
    dy = fabs(y1 - y0);

    ponto(px, py);

    incx = 1;
    if(x1 < x0){
        incx = -1;
    }
    incy = 1;
    if(y1 < y0){
        incy = -1;
    }
    
    if(dx > dy){
        par1 = 2*dy;
        par2 = 2*(dy - dx);
        pk = 2*dy - dx;
        for(i=0; i<dx; i++){
            if(pk>=0){
                py += incy;
                pk += par2;
            }else{
                pk += par1;
            }
            px += incx;
            ponto(px, py);
        }
    }else{
        par1 = 2*dx;
        par2 = 2*(dx - dy);
        pk = 2*dx - dy;
        for(i=0; i<dy; i++){
            if(pk>=0){
                px += incx;
                pk += par2;
            }else{
                pk += par1;
            }
            py += incy;
            ponto(px, py);
        }
    }
}

void triangulo(int x0, int y0, int x1, int y1, int x2, int y2){
    linha(x0, y0, x1, y1);
    linha(x1, y1, x2, y2);
    linha(x0, y0, x2, y2);
}

void desenha(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(R, G, B);
    glPointSize(5);
    if(control==0){
        linha(posx0, posy0, posx1, posy1);
    }else{
        triangulo(posx0, posy0, posx1, posy1, posx2, posy2);
    }
    glFlush();
}

void mouse(int botao, int estado, int x, int y){
    switch(botao) {
        case GLUT_LEFT_BUTTON:
            if(estado==GLUT_DOWN){
                if(control==0){
                    if(count%2==0){
                        posx0 = x;
                        posy0 = y;
                        count++;
                    }else{
                        posx1 = x;
                        posy1 = y;
                        count++;
                    }
                }else{
                    if(count%3==0){
                        posx0 = x;
                        posy0 = y;
                        count++;
                    }else if(count%2==0){
                        posx1 = x;
                        posy1 = y;
                        count++;
                    }else{
                        posx2 = x;
                        posy2 = y;
                        count++;
                    }
                }
            }   
            break;
        default:
            break;
    }
    if(control==0 && count%2==0){
        glutPostRedisplay();
    }
    if(control==1 && count%3==0){
        glutPostRedisplay();
    }
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
        case 'r':
        case 'R': control = 0; count = 0; break;
        case 't':
        case 'T': control = 1; count = 0; break;
    }
    glutPostRedisplay();
}

int main (int argc, char * argv [] ){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercicio 02 - Bresenham");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}