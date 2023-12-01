#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NO_TEXTURES 6


float thetaX = 0.0;
float thetaY = 0.0;
float posicaoBracosZ = 0.0, posicaoBracosY = 0.0, posicaoPernasZ =0.0, posicaoPernasX = 0.0;

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 6

/* vetor com os números das texturas */
GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "earthTexture.bmp",
        "surface1.bmp",
        "surface2.bmp",
        "surface3.bmp",
        "surface4.bmp",
        "surface5.bmp"
};


GLUquadricObj *obj;

void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}

void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id);
    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void initTexture (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
  //  CarregaTextura("tunnelTexture.bmp");
    //CarregaTextura("tex2.bmp");
    CarregaTexturas();

}

void iluminacao()
{
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    GLfloat light1_pos[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0f);               //espalhamento angular
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);              //atenuação angular

    //Parâmetros definidos globalmente
    //GLfloat global_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    ////Reflexão especular definida como a posição de visão corrente
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    ////Habilitar cálculos de iluminação para ambas as faces dos polígonos
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void cubo()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-0.25,0.25,0.25);
    glVertex3f(0.25,0.25,0.25);
    glVertex3f(0.25,-0.25,0.25);
    glVertex3f(-0.25,-0.25,0.25);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-0.25,0.25,-0.25);
    glVertex3f(0.25,0.25,-0.25);
    glVertex3f(0.25,-0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
    glEnd();

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.25,-0.25,0.25);
    glVertex3f(0.25,0.25,0.25);
    glVertex3f(0.25,0.25,-0.25);
    glVertex3f(0.25,-0.25,-0.25);
    glEnd();

    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-0.25,-0.25,0.25);
    glVertex3f(-0.25,0.25,0.25);
    glVertex3f(-0.25,0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
    glEnd();

    glColor3f(1.0,0.0,1.0);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-0.25,0.25,0.25);
    glVertex3f(0.25,0.25,0.25);
    glVertex3f(0.25,0.25,-0.25);
    glVertex3f(-0.25,0.25,-0.25);
    glEnd();

    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-0.25,-0.25,0.25);
    glVertex3f(0.25,-0.25,0.25);
    glVertex3f(0.25,-0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
    glEnd();
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.5,2.5,-2.5,2.5,-10,10);
    iluminacao();
}

void desenha_cabeca()
{
    glPushMatrix();
    glTranslated(0, 2, 0);
    cubo();
    glPopMatrix();
}

void desenha_tronco()
{
    glPushMatrix();
    glTranslated(0, 1.2, 0);
    glScaled(1.1, 1.8, 1);
    cubo();
    glPopMatrix();
}

void desenha_braco_direito()
{
    glPushMatrix();
    glScalef(1.2, 0.5, 0.5);
    glTranslated(0.55, 3, 0);
    cubo();
    glPopMatrix();

}

void desenha_braco_esquerdo()
{
    glPushMatrix();
    glScalef(1.2, 0.5, 0.5);
    glTranslated(-0.55, 3, 0);
    cubo();
    glPopMatrix();
}

void desenha_atebraco_direito()
{
    glPushMatrix();
    glScalef(1.12, 0.5, 0.5);
    glTranslated(1.15, 3, 0);
    cubo();
    glPopMatrix();

}

void desenha_antebraco_esquerdo()
{
    glPushMatrix();
    glScalef(1.12, 0.5, 0.5);
    glTranslated(-1.15, 3, 0);
    cubo();
    glPopMatrix();

}

void desenha_perna_direita()
{
    glPushMatrix();
    glScalef(0.55, 1.4, 0.9);
    glTranslated(0.3, 0.2, 0);
    cubo();
    glPopMatrix();

}

void desenha_perna_esquerda()
{
    glPushMatrix();
    glScalef(0.55, 1.4, 0.9);
    glTranslated(-0.3, 0.2, 0);
    cubo();
    glPopMatrix();
}

void desenha_canela_direita()
{
    glPushMatrix();
    glScalef(0.55, 1.4, 0.9);
    glTranslated(-0.3, -0.35, 0);
    cubo();
    glPopMatrix();

}

void desenha_canela_esquerda()
{
    glPushMatrix();
    glScalef(0.55, 1.4, 0.9);
    glTranslated(0.3, -0.35, 0);
    cubo();
    glPopMatrix();
}

void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslated(0, -0.5, 0);
    glRotated(thetaX, 1, 0, 0);
    glRotated(thetaY, 0, 1, 0);

    desenha_cabeca();
    desenha_tronco();



    glPushMatrix();
    glTranslated(0.45, 1.52, 0);
    glRotated(posicaoBracosZ, 0, 0, 1);
    glRotated(posicaoBracosY, 0, 1, 0);
    glTranslated(-0.45, -1.52, 0);
    desenha_braco_direito();
    desenha_atebraco_direito();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0.45, 1.52, 0);
    glRotated(-posicaoBracosZ, 0, 0, 1);
    glRotated(-posicaoBracosY, 0, 1, 0);
    glTranslated(0.45, -1.52, 0);
    desenha_braco_esquerdo();
    desenha_antebraco_esquerdo();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.193, 0.8, 0);
    glRotated(posicaoPernasZ, 0, 0, 1);
    glRotated(posicaoPernasX, 1, 0, 0);
    glTranslated(-0.193, -0.8, 0);
    desenha_perna_direita();
    desenha_canela_esquerda();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.193, 0.8, 0);
    glRotated(-posicaoPernasZ, 0, 0, 1);
    glRotated(posicaoPernasX, 1, 0, 0);
    glTranslated(0.193, -0.8, 0);
    desenha_perna_esquerda();
    desenha_canela_direita();
    glPopMatrix();

    glPopMatrix();


    glFlush();
}

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_RIGHT:
        posicaoBracosZ += 2;
        break;
    case GLUT_KEY_LEFT:
        posicaoBracosZ -= 2;
        break;
    case GLUT_KEY_UP:
        posicaoBracosY += 2;
        break;
    case GLUT_KEY_DOWN:
        posicaoBracosY -= 2;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':
        posicaoPernasZ -= 2;
        break;
    case 'd':
    case 'D':
        posicaoPernasZ += 2;
        break;
    case 'w':
    case 'W':
        posicaoPernasX += 2;
        break;
    case 's':
    case 'S':
        posicaoPernasX -= 2;
        break;
    case '1':
        thetaY += 2;
        break;
    case '2':
        thetaY -= 2;
        break;
    default :
        break ;
    }
    glutPostRedisplay() ;
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutCreateWindow("Cubo");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(tecladoEspecial);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}