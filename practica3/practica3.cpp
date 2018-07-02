#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

/*  Practica 3

1. Disela un robot en 2d sobre una hoja cuadriculada o milimetrica, utilizando
las primitivas que ya conoces com: poligonos cuadros, triangulos, lineas y puntos.

2. Utilia el codigo de la practica anterior de nombre 02_Transformaciones_calculo.cpp

3. Ajusta las variables (rango) de las coordenasa de vision del mundo parapoder trabajar
sobre los 4 cuadrantes del plano cartsiano

4. Identifica los valores de los certices que definen las partes del robot(x,y) en tu hoja
de cuadricula o milimetrica. Recuerda que el valor de z lo asumimos como 0 para todos
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
GLsizei winWidth=900, winHeight=600;

// rango para las coordenadas de visión del mundo
GLfloat xwcMin=0.0, xwcMax=1200.0;
GLfloat ywcMin=0.0, ywcMax=900.0;



void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
}



void displayFcn(void){

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
