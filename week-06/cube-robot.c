// Nome: Éric Fadul Cunha Yoshida RA: 148143

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 0.0;
float thetaY = 0.0;

float rotx = 0.0;
float roty = 0.0;

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

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
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


/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                /* texture_id = vetor que guardas os números das texturas */

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

/* **********************************************************************
  void initTexture(void)
        Define a textura a ser usada

 ********************************************************************** */
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

void lightning(){
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    //Atenuação radial
    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);   //define a0
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);    //define a1
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);  //define a2

    //Fonte de Luz Direcional - Efeito de Holofote
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
    lightning();
}

void cubo(){
     float size = 1.0;
     GLfloat n[6][3] =
     {
        {-0.25, 0.25, 0.25},
        {0.25, 0.25, 0.25},
        {0.25, 0.25, 0.25},
        {0.25, -0.25, 0.25},
        {0.25, 0.25, 0.25},
        {0.25, 0.25, -0.25}
     };
     GLint faces[6][4] =
     {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
     };
     GLfloat v[8][3];
     GLint i;

     v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
     v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
     v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
     v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
     v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
     v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

     for (i = 5; i >= 0; i--) {
         glBindTexture(GL_TEXTURE_2D, texture_id[i]);
         glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0.0f,0.0f);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1.0f,0.0f);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1.0f,1.0f);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0.0f,1.0f);
            glVertex3fv(&v[faces[i][3]][0]);
         glEnd();
     }
}

void cabeca(){
    glTranslatef(0.0, 2.95, 0.0);
    cubo();
}

void torso(){
    glTranslatef(0.0, 0.9, 0.0);
    glScalef(1.0, 3.0, 1.0);
    cubo();
}

void bracoesq(){
    glTranslatef(-0.5, 1.8, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.6, 1.2, 0.6);
    cubo();
    
    glPopMatrix(); //p rot

    glTranslatef(-1.75, 1.8, 0.0);
    glRotatef(90-2*thetaX, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.6, 1.2, 0.6);
    cubo();
}
void bracodir(){
    glTranslatef(0.5, 1.8, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.6, 1.2, 0.6);
    cubo();

    glPopMatrix();  //p rot

    glTranslatef(1.75, 1.8, 0.0);
    glRotatef(-90+2*thetaX, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.6, 1.2, 0.6);
    cubo();
}

void pernaesq(){

    glTranslatef(-0.26, -0.74, 0.0);
    glRotatef(180, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.5, 1.2, 0.6);
    cubo();

    glPopMatrix();

    glTranslatef(-0.26, -2.0, 0.0);
    glRotatef(180, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.5, 1.2, 0.6);
    cubo();
}

void pernadir(){

    glTranslatef(0.26, -0.74, 0.0);
    glRotatef(-180, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.5, 1.2, 0.6);
    cubo();

    glPopMatrix();

    glTranslatef(0.26, -2.0, 0.0);
    glRotatef(-180, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.5, 1.2, 0.6);
    cubo();
}

void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a de modelo

    glPushMatrix(); //iden
    glRotatef(rotx, 1.0, 0.0, 0.0);
    glRotatef(roty, 0.0, 1.0, 0.0);
    glPushMatrix();  //rot

    cabeca();

    glPopMatrix();  //prot
    glPushMatrix();  //rot

    torso();

    glPopMatrix();  //prot
    glPushMatrix();  //rot

    glTranslatef(-0.3, 1.5, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glRotatef(-thetaX, 0.0, 0.0, 1.0);
    glTranslatef(0.3, -1.5, 0.0);
    glPushMatrix();  //rotaçao braço
    bracoesq();

    glPopMatrix();  //p iden
    glPushMatrix();  //iden

    glTranslatef(0.3, 1.5, 0.0);
    glRotatef(-thetaY, 0.0, 1.0, 0.0);
    glRotatef(thetaX, 0.0, 0.0, 1.0);
    glTranslatef(-0.3, -1.5, 0.0);
    glPushMatrix();
    bracodir();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-0.15, 0.3, 0.0);
    glRotatef(-thetaX, 0.0, 0.0, 1.0);
    glTranslatef(0.15, -0.3, 0.0);
    glPushMatrix();
    pernaesq();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.15, 0.3, 0.0);
    glRotatef(thetaX, 0.0, 0.0, 1.0);
    glTranslatef(-0.15, -0.3, 0.0);
    glPushMatrix();
    pernadir();

    glPopMatrix();
    glPopMatrix();
    glFlush();
}

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_RIGHT:
        thetaY += 2;
        break;
    case GLUT_KEY_LEFT:
        thetaY -= 2;
        break;
    case GLUT_KEY_UP:
        thetaX += 2;
        break;
    case GLUT_KEY_DOWN:
        thetaX -= 2;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y){
    switch(key){
        case '1': rotx+=2; break;
        case '2': rotx-=2; break;
        case '3': roty+=2; break;
        case '4': roty-=2; break;
        case '5': glBindTexture(GL_TEXTURE_2D, texture_id[0]); break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Robo");
    glutDisplayFunc(desenha);
    glutSpecialFunc(tecladoEspecial);
    glutKeyboardFunc(teclado);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}