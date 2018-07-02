#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

/*  Practica 4

1.Retoma la practica anterior (dibujo con triangulso y transformaciones) y crea
una copia para trabajar sobre ella

2. Llama en el main() a la funcion glutKeyboardFunc() preferentemente antes de
glutDisplayFunc()

3. Crea la funcion de callback para glutKeyboardFunc(),de nombre "ControlTeclado"
que se ajuste al prototipo de notas. por ahora dejala vacia

4. Crea variables globales que sean necesarias para: Transicion, Rotacion, Esclamiento

5. Investiga para que sirve o en que momento se utiliza la funcion glutPostRedisplay();

6. Programa el comportamiento de la funcion ControlTeclado, si olvidar invocar a
la funcion glutPostRedisplay() antes de cerrar la funcion

7. Toma uno o varios e los objetos pintdos en la escena y aplicale la transformaciones
de traslacion parametrizada por las variables globales tx y ty

8. Ajusta los incrementos para que no sean demasiado grandes ni muy pequeños

9. LLama en el main() a las funciones glutMouseFunc() y glutMotionFunc() para configurar
los eventos en el Mouse

10. CRea la funcion callback para glutMouseFunc() de nombre onMouse o cualquier nombre que
se elija pero que coincida con el prototipo establecido en las notas y agregar el siguiente codigo
(Buscar codigo en diapos)

11. Crea la funcion callback glutMotionFunc() de nombre onMotion y agrega el siguiente codigo (en diapos)

12. Crear a inicializar las variables que hagan falta para las actividades 10 y 11

13. Toma el mismo objeto seleccionado de la escena y aplicale la transformacion de Rotacion
parametrizada por la variable global rz

14. Toma el mismo objeto seleccionado de la escena y aplciale tranformacion de
esalamiento parametrizada por las variables globales sx, sy, y sz, donde el
escalamiento en Z siempre es 1.0

15. CRea la funcion glut correspondiente a la administacion de MEnus y sub-Menus

16. Crea la funcion callbaclk que se encarhara de modificar el color tanto de rellenado
de algunas figuras como el de fondo de la escena 2d usando una matriz de colores definida

IMPORTANTE: Para mas detalles del uso de esta matriz de colores, consulta el codigo ejemplo de
nombre 04_menu.cpp adjunto en las notas

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
