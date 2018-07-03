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

11. Crea la funcion callback glutMotionFunc() de nombre onMotion
y agrega el siguiente codigo (en diapos)

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

//Variables globales trasicion
GLfloat xTrans=1.0, yTrans=1.0,  zTrans=1.0;
//Variables globales escalar
GLfloat xEsc=1.0, yEsc=1.0,  zEsc=1.0;
//Variables globales rotar
GLfloat angulo=0.0, xRot=0.0, yRot=0.0,  zRot=1.0;

//Menu de figuras a elegir
typedef enum{F1,F2,F3,F4,F5,F6,F7,F8,F9,F10}opcionMenu;

float colorx=1.0, colory=0.0, colorz=0.0;

float colores[8][3] =
{
    { 1.00f, 1.00f, 1.00f}, // 0 - blanco
    { 0.00f, 0.00f, 0.00f}, // 1 - negro
    { 1.00f, 0.00f, 0.00f}, // 2 - rojo
    { 0.50f, 0.26f, 0.12f}, // 3 - rojo claro
    { 0.00f, 1.00f, 0.00f}, // 4 - verde
    { 0.06f, 0.25f, 0.13f}, // 5 - verde oscuro
    { 0.00f, 0.00f, 1.00f}, // 6 - azul
    { 0.85f, 0.95f, 1.00f}, // 7 - azul claro
};



void init(void)
{
  glClearColor(1.0,1.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void triangulo(){
  glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);
	glColor3f(colorx,colory,colorz);
	glBegin(GL_TRIANGLES);
	glVertex3f(100.0,100.0,0.0);
  glVertex3f(300.0,300.0,0.0);
  glVertex3f(100.0,400.0,0.0);
	glEnd();
	glFlush();
}


void displayFcn(void){

  glPushMatrix();
  glTranslated(xTrans,yTrans,zTrans);
  glRotated(angulo,xRot,yRot,zRot);
  glScalef(xEsc,yEsc,zEsc);
  triangulo();
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

void controlTeclado(unsigned char c, int x, int y){

switch (c) {
	case 'd':
	     //traslacion derech
       xTrans+=10.0;
	    break;
  case 'a':
    	//traslacion izquierda
     xTrans-=10.0;
      break;
	case 'w':
			//traslacion arriba
      yTrans+=10.0;
			break;
	case 'z':
			 //traslacion abajo
       yTrans-=10.0;
			break;
  case 's':
      //escalamiento agrandar
      xEsc+=0.01;
      yEsc+=0.01;
     break;

    case 'x':
         //escalamiento reducir
         xEsc-=0.01;
         yEsc-=0.01;
        break;

        case 'g':
             //girar a la derecha
             angulo+=5;
            break;
        case 'b':
            //girar a la derecha
             angulo-=5;
             break;


}


glutPostRedisplay();
}

/* Actividad 5

glutPostRedisplay() essentially sets a flag so that on
the next iteration of the mainloop, your registered display()
function is called. If you don't tell the mainloop it needs to draw the next
frame with a glutPostRedisplay (ie imagine commenting out glutPostRedisplay
in drive(data) above) then your animation will look as if it is stuck ie
no animation even though the x,y,z position of the "car" will be changing!

*/
void onMouse(int button, int state, int x, int y){
  // MANEJO DE ROTACIÓN -> VINCULADO CON EL MOVIMIENTO DEL MOUSEi.e.onMotion()
if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN)){
// nx=x;
// ny=y;
}
 //MANEJO DE ESCALAMIENTO
if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN)){
  xEsc+=0.5;
  yEsc+=0.5;
}
if((button==GLUT_RIGHT_BUTTON)&&(state==GLUT_DOWN)){
xEsc-=0.5;
yEsc-=0.5;
}
glutPostRedisplay();
}

void onMotion(int x, int y){
  angulo+=0.5;
  glutPostRedisplay();

}

//Creacion de menu y submenus
void menuPosicionCamara(int opcion)
{
	switch(opcion)
	{
		case F1:
     colorx=colores[0][0], colory=colores[0][1], colorz=colores[0][2];
			break;
		case F2:
    colorx=colores[1][0], colory=colores[1][1], colorz=colores[1][2];
			break;
		case F3:
		 colorx=colores[2][0], colory=colores[2][1], colorz=colores[2][2];
			break;
		case F4:
	   colorx=colores[3][0], colory=colores[3][1], colorz=colores[3][2];
		 break;
		 case F5:
 			colorx=colores[4][0], colory=colores[4][1], colorz=colores[4][2];
 		 break;
		 case F6:
 			colorx=colores[5][0], colory=colores[5][1], colorz=colores[5][2];
 		 break;
     case F7:
 			colorx=colores[6][0], colory=colores[6][1], colorz=colores[6][2];
 		 break;
     case F8:
 			colorx=colores[7][0], colory=colores[7][1], colorz=colores[7][2];
 		 break;
     case F9:
       glPolygonMode(GL_FRONT, GL_FILL);
      break;

    case F10:
     glPolygonMode(GL_FRONT, GL_LINE);
      break;


	}

	glutPostRedisplay();
}

void creacionMenu(void)
{
	int menuColores,menuMain;

	menuColores = glutCreateMenu(menuPosicionCamara);
	glutAddMenuEntry("Blanco", F1);
	glutAddMenuEntry("Negro", F2);
	glutAddMenuEntry("Rojo", F3);
	glutAddMenuEntry("Rojo claro", F4);
	glutAddMenuEntry("Verde", F5);
	glutAddMenuEntry("Verde oscuro", F6);
  glutAddMenuEntry("Azul", F7);
  glutAddMenuEntry("Azul oscuro", F8);
  glutAddMenuEntry("Con relleno", F9);
  glutAddMenuEntry("Sin relleno" , F10);

	menuMain = glutCreateMenu(menuPosicionCamara);
    glutAddSubMenu("Colores y relleno", menuColores);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
  creacionMenu();
	glutDisplayFunc(displayFcn);
  glutKeyboardFunc(controlTeclado);
	glutReshapeFunc(winReshapeFcn);
  glutMouseFunc(onMouse);
  glutMotionFunc(onMotion);
	glutMainLoop();
}
