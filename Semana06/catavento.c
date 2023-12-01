//Nome: Eric Fadul Cunha Yoshida RA: 148143

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.141592654

int posx0 = 300, posy0 = 300, raio = 10;
float R = 1.0, G = 0.0, B = 0.0;
int control = 0;
float angZ = 0.0;
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

void triangulo(){
    glBegin(GL_POLYGON);
        glVertex2f(1.0, 1.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(1.0, 0.0);
    glEnd();
}

void desenha(){
    init();

    glPushMatrix(); //iden

    glRotatef(angZ,0.0,0.0,1.0);

    glColor3f(1.0, 0.0, 0.0);
    triangulo();

    glColor3f(0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    triangulo();

    glColor3f(0.8, 0.2, 0.2);
    glRotatef(90, 0.0, 0.0, 1.0);
    triangulo();

    glColor3f(0.0, 0.0, 1.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    triangulo();

    glPopMatrix();

    glFlush();
}

void anima()
{
    switch (opcao) {
        case 1:
            angZ+=0.05;
            break;
        case 2:
            angZ-=0.05;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void rotacoes(int key, int x, int y){
     glutIdleFunc(anima);
     switch (key){
        case GLUT_KEY_UP :
           opcao = 1;
           break ;
        case GLUT_KEY_DOWN :
           opcao = 2;
           break ;
        case GLUT_KEY_LEFT :
           opcao = 3;
           break ;
        case GLUT_KEY_RIGHT :
           glutIdleFunc(NULL);
           opcao = 4;
           break ;
        default:
           break;
     }
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
    glutCreateWindow("Catavento");
    glutDisplayFunc(desenha);
    glutSpecialFunc(rotacoes);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}