/*  Practica 6
 1. Modifica la posicion y la orientacion de la camara en la ventana "NAVE 3D: vista... "
 y crea los menus que sean necesarios para seleccionar enttre los diferentes tipos
 Frontal, trasera, lateral izquierda, lateral derecha, superior, inferiorr
 2. Para esto modifica las variables globales asociadas a la funcion
 gluLookAt()
 3. Agrega un menu para elegir entre modo solido o alambre{}
*/
//#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

#include <iostream>

using namespace std;

//Menu de figuras a elegir
typedef enum{F1,F2,F3,F4,F5,F6,F7,F8,F9,C1,C2,C3,C4,C5,C6,C7,C8,C9,E1,E2,D1,D2,S1,S2}opcionMenu;

int bandera1=0, bandera2=0;

	//Matriz de colores
	float colores[4][3]=
	{
	    {1.0,1.0,1.0}, //0 blanco
		{1.0,0.0,0.0}, //1 rojo
		{0.0,1.0,0.0}, //2 verde
		{0.0,0.0,1.0}, //3 azul
	};

	//variables globales para la rotación
	float alpha=45, beta=45;

	//variables globales para la cámara
	float eyeX=0.0f, eyeY=0.0f, eyeZ=5.0f;
	float oriX=0.0f, oriY=1.0f, oriZ=0.0f;

    //variables globales para el cálculo de los grados
	int x0, y0;


void luzAmbiental(void)
{
	GLfloat l_difusa[]={0.5f, 0.5f, 0.5f, 0.0f};
	GLfloat l_especular[]={0.5f, 0.5f, 0.5f, 0.0f};
	GLfloat l_posicion[]={1.0, 1.0, 1.0, 0.0};

	GLfloat l_ambiente[]={1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,l_ambiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambiente);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);

	glEnable (GL_LIGHT0);
}

void init(void)
{
	luzAmbiental();
	glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void display1(void)
{
/*
eyeX=3.0f, eyeY=1.0f, eyeZ=5.0f;
oriX=0.0f, oriY=1.0f, oriZ=0.0f;
*/

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	gluLookAt(eyeX, eyeY, eyeZ,
			  0.0f, 0.0f, 0.0f,
			  oriX, oriY, oriZ);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
      if(bandera1==0){
				glutSolidTeapot(0.5);
			}else{
				glutWireTeapot(0.5);
			}

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void display2(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
if(bandera2==0){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	gluLookAt(0.0f, 0.0f, 5.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
			glutSolidTeapot(0.5);
				//glutWireTeapot(0.5);
	glPopMatrix();
}else{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	gluLookAt(0.0f, 0.0f, 5.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
			//glutSolidTeapot(0.5);
			glutWireTeapot(0.5);
	glPopMatrix();
}
	glFlush();
	glutSwapBuffers();
}

//Accion del mouse
void onMouse(int button, int state, int x, int y)
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) )
	{
		x0 = x;
		y0 = y;

// std::cout << " eyeX="<<eyeX <<" eyeY="<<eyeY << "eyeZ="<<eyeZ<<'\n';
// std::cout << " oriX="<< oriX <<" oriY="<< oriY << " eyeZ=" <<oriZ<<'\n';
	}
}

//Incremento o decremente de los angulos de rotacion
void onMotion(int x, int y)
{
	alpha = (alpha + (y - y0));
	beta = (beta + (x - x0));
	x0 = x; y0 = y;
	glutPostRedisplay();
}


void menuPosicionCamara(int opcion)
{
	switch(opcion)
	{
		case F1:
			//Frontal *
			eyeX=0.0f, eyeY=0.0f, eyeZ=5.0f;
			oriX=0.0f, oriY=1.0f, oriZ=0.0f;
			break;
		case F2:
			//Trasera
			eyeX=0.0f, eyeY=5.0f, eyeZ=1.0f;
			oriX=0.0f, oriY=1.0f, oriZ=0.0f;
			break;
		case F3:
		//Lateral Izquierda *
		eyeX=-10.0f, eyeY=0.0f, eyeZ=0.0f;
		oriX=0.0f, oriY=1.0f, oriZ=0.0f;
			break;
		case F4:
			//Latera derecha *
			eyeX=10.0f, eyeY=0.0f, eyeZ=0.0f;
			oriX=0.0f, oriY=1.0f, oriZ=0.0f;
		 break;
		 case F5:
 			//Superior *
			eyeX=0.0f, eyeY=5.0f, eyeZ=1.0f;
			oriX=0.0f, oriY=1.0f, oriZ=0.0f;
 		 break;
		 case F6:
 			//Inferior
			eyeX=0.0f, eyeY=-5.0f, eyeZ=1.0f;
			oriX=0.0f, oriY=1.0f, oriZ=0.0f;
 		 break;

		 case F7:
       bandera1=0;
			 bandera2=0;
			 	glutPostRedisplay();
		   break;

			 case F8:
	       bandera1=1;
				 bandera2=1;
				 	glutPostRedisplay();
			   break;

	}

	glutPostRedisplay();
}

//Creacion de menu y submenus
void creacionMenu(void)
{
	int menuCAMARA,menuMain;

	menuCAMARA = glutCreateMenu(menuPosicionCamara);
	glutAddMenuEntry("Frontal", F1);
	//glutAddMenuEntry("Trasera", F2);
	glutAddMenuEntry("Lateral izquiera", F3);
	glutAddMenuEntry("Lateral derecha", F4);
	glutAddMenuEntry("Superior", F5);
	glutAddMenuEntry("Inferior", F6);
  glutAddMenuEntry("Modo solido", F7);
	glutAddMenuEntry("Modo alambre", F8);

	menuMain = glutCreateMenu(menuPosicionCamara);
    glutAddSubMenu("Camara", menuCAMARA);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}




int main(int argc, char *argv[])
{
	glutInit( & argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("NAVE 3D: Vista Ortogonal");
	init();
	creacionMenu();
	glutDisplayFunc(display1);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(615, 100);
	glutCreateWindow("NAVE 3D: Vista en Perspectiva");
	init();
	glutDisplayFunc(display2);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);

	glutMainLoop();

	return 0;
}
