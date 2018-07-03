#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>

/*  Practica 3

1. Disela un robot en 2d sobre una hoja cuadriculada o milimetrica,
 utilizandolas primitivas que ya conoces com: poligonos cuadros,
 triangulos, lineas y puntos.

2. Utilia el codigo de la practica anterior de nombre
02_Transformaciones_calculo.cpp

3. Ajusta las variables (rango) de las coordenasa de vision
del mundo parapoder trabajar sobre los 4 cuadrantes del
plano cartsiano

4. Identifica los valores de los vertices que definen las
partes del robot(x,y) en tu hoja de cuadricula o milimetrica.
Recuerda que el valor de z lo asumimos como 0 para todos
los vertices

****************** Actividades (Entregable 1) **************************

1.En la ventana principal grafica el robor con los vertices previamente identificados
utilizando poligonos, cuadros triangulos, etc.

2.En una nueva ventana grafica elmismo Robot utilizando solamente primitivas triangulares
(GL_TRIANGLES,GL_TRIANGLE_STRIP,GLTRIANGLE_FAN)

3. Considera el uso del rellenado con colores para identificar los elementos que componen
cada parte del robot

Importante: No deben utilizarse transformaciones todavia, todo es a traves de la
definicion de los vertices de cada parte del robot

************************ Entregable 2 ********************************

1. Crea un nuevo programa para este entregable e identifica las piezas o partes finales
mas importantes del robot

2. Crea una funcion para cada parte identificada en el paso anterior y graficala
considerando: Utilizar solo triangulos, mantener el centro (centroide) cada parte en la
posicion (0,0) del plano 2D, Aplicar transformaciones de openGl de la funcion, solo en
caso de que la parte qye se esta graficando este compuesta de mas partes pequeñas. Por ejemplo una pierna

3. En la ventana principal invoca las funciones cabeza, brazo, pierna etc. dentro de la funcionde
de graficado (display) y aplica aqui las transformaciones opengl correspondientes

4. Invoca doa o mas veces la funcion de la parte del robot que necesites, evta el uso
repetido de FUNCIONES

5. Crea una nueva ventana y modificando las piezas (no sus vertices) crea una version distinta


*/

// Tamaño inicial de la ventana de despliegue
GLsizei winWidth=500, winHeight=500;

// rango para las coordenadas de visión del mundo
GLfloat xwcMin=-500.0, xwcMax=500.0;
GLfloat ywcMin=-500.0, ywcMax=500.0;


void init(void)
{
  glClearColor(1.0,1.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void cabeza(){
	//Cabeza
  glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(-60.0,260.0,0.0);
	glVertex3f(-60.0,360.0,0.0);
	glVertex3f(80.0,360.0,0.0);
	glVertex3f(80.0,260.0,0.0);
	glEnd();
  //Cuello
	glColor3f(0.0,0.0,0.0);//Negro
	glBegin(GL_QUADS);
	glVertex3f(-20.0,220.0,0.0);
	glVertex3f(-20.0,260.0,0.0);
	glVertex3f(40.0,260.0,0.0);
	glVertex3f(40.0,220.0,0.0);
	glEnd();
	//Ojo derecho
  glColor3f(255/255.0f,140/255.0f,0/255.0f);//Dark orange
  glBegin(GL_QUADS);
  glVertex3f(20.0,320.0,0.0);
  glVertex3f(20.0,340.0,0.0);
  glVertex3f(60.0,340.0,0.0);
  glVertex3f(60.0,320.0,0.0);
  glEnd();
//Ojo izquierdo
glColor3f(255/255.0f,140/255.0f,0/255.0f);//Dark orange
glBegin(GL_QUADS);
glVertex3f(-40.0,320.0,0.0);
glVertex3f(-40.0,340.0,0.0);
glVertex3f(0.0,340.0,0.0);
glVertex3f(0.0,320.0,0.0);
glEnd();
//Boca
glColor3f(255/255.0f,140/255.0f,0/255.0f);//Dark orange
glBegin(GL_QUADS);
glVertex3f(-40.0,280.0,0.0);
glVertex3f(-40.0,300.0,0.0);
glVertex3f(60.0,300.0,0.0);
glVertex3f(60.0,280.0,0.0);
glEnd();
	glFlush();
}

void torso(){
	//torso
  glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(-120.0,60.0,0.0);
	glVertex3f(-120.0,220.0,0.0);
	glVertex3f(140.0,220.0,0.0);
	glVertex3f(140.0,60.0,0.0);
	glEnd();
	//Cintura
	glColor3f(0.0,0.0,0.0);//Negro
	glBegin(GL_QUADS);
	glVertex3f(-60.0,-20.0,0.0);
	glVertex3f(-60.0,60.0,0.0);
	glVertex3f(80.0,60.0,0.0);
	glVertex3f(80.0,-20.0,0.0);
	glEnd();
	//Cadera
	glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(-100.0,-120.0,0.0);
	glVertex3f(-100.0,-20.0,0.0);
	glVertex3f(120.0,-20.0,0.0);
	glVertex3f(120.0,-120.0,0.0);
	glEnd();
	glFlush();
}

void brazo(){
	//Hombro
	glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(140.0,160.0,0.0);
	glVertex3f(140.0,220.0,0.0);
	glVertex3f(280.0,220.0,0.0);
	glVertex3f(280.0,160.0,0.0);
	glEnd();
	//Brazo
	glColor3f(0.0,0.0,0.0);//Negro
	glBegin(GL_QUADS);
	glVertex3f(180.0,-60.0,0.0);
	glVertex3f(180.0,160.0,0.0);
	glVertex3f(240.0,160.0,0.0);
	glVertex3f(240.0,-60.0,0.0);
	glEnd();
	//Mano
	glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(160.0,-120.0,0.0);
	glVertex3f(160.0,-60.0,0.0);
	glVertex3f(260.0,-60.0,0.0);
	glVertex3f(260.0,-120.0,0.0);
	glEnd();
	//Dedo gordo
	glColor3f(190/255.0f,190/255.0f,190/255.0f);//gray
	glBegin(GL_QUADS);
	glVertex3f(140.0,-100.0,0.0);
	glVertex3f(140.0,-60.0,0.0);
	glVertex3f(160.0,-60.0,0.0);
	glVertex3f(160.0,-100.0,0.0);
	glEnd();
	//Dedo 1
	glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(240.0,-180.0,0.0);
	glVertex3f(240.0,-120.0,0.0);
	glVertex3f(260.0,-120.0,0.0);
	glVertex3f(260.0,-180.0,0.0);
	glEnd();
	//Dedo 2
	glColor3f(190/255.0f,190/255.0f,190/255.0f);//gray
	glBegin(GL_QUADS);
	glVertex3f(220.0,-180.0,0.0);
	glVertex3f(220.0,-120.0,0.0);
	glVertex3f(240.0,-120.0,0.0);
	glVertex3f(240.0,-180.0,0.0);
	glEnd();
	//Dedo 3
	glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(200.0,-180.0,0.0);
	glVertex3f(200.0,-120.0,0.0);
	glVertex3f(220.0,-120.0,0.0);
	glVertex3f(220.0,-180.0,0.0);
	glEnd();
	//Dedo 4
	glColor3f(190/255.0f,190/255.0f,190/255.0f);//gray
	glBegin(GL_QUADS);
	glVertex3f(180.0,-180.0,0.0);
	glVertex3f(180.0,-120.0,0.0);
	glVertex3f(200.0,-120.0,0.0);
	glVertex3f(200.0,-180.0,0.0);
	glEnd();

	glFlush();
}

void pierna(){
	//Pierna
	glColor3f(0.0,0.0,0.0);//Negro
	glBegin(GL_QUADS);
	glVertex3f(40.0,-360.0,0.0);
	glVertex3f(40.0,-120.0,0.0);
	glVertex3f(100.0,-120.0,0.0);
	glVertex3f(100.0,-360.0,0.0);
	glEnd();
	//Zapato
	glColor3f(190/255.0f,190/255.0f,190/255.0f);//gray
	glBegin(GL_QUADS);
	glVertex3f(40.0,-400.0,0.0);
	glVertex3f(40.0,-360.0,0.0);
	glVertex3f(140.0,-360.0,0.0);
	glVertex3f(140.0,-400.0,0.0);
	glEnd();
	glColor3f(112/255.0f,128/255.0f,144/255.0f);//slate gray
	glBegin(GL_QUADS);
	glVertex3f(40.0,-460.0,0.0);
	glVertex3f(40.0,-400.0,0.0);
	glVertex3f(180.0,-400.0,0.0);
	glVertex3f(180.0,-460.0,0.0);
	glEnd();

	glFlush();
}



void displayFcn(void){
cabeza();
torso();
brazo();
glPushMatrix();
glTranslatef(20.0f,1.0f,1.0f);
glScalef(1, -1, 1);
glRotated(180.0,0.0,0.0,1.0);
brazo();
glPopMatrix();
pierna();
glPushMatrix();
glTranslatef(20.0f,1.0f,1.0f);
glScalef(1, -1, 1);
glRotated(180.0,0.0,0.0,1.0);
pierna();
glPopMatrix();

	glFlush();
}


// FUNCIÓN QUE REAJUSTA EL TAMAÑO DE LA VENTANA
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

// MAIN: ADMINISTRACIÓN DE FUNCIONES PRINCIPALES --------------------------------------------------------------------

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("Robot");
	init();

	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();
}
