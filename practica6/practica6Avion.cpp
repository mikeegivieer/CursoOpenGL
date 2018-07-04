#include <GL/glut.h>
#include <stdio.h>

#include <iostream>

using namespace std;

//Menu de figuras a elegir
typedef enum{F1,F2,F3,F4,F5,F6,F7,F8,F9,C1,C2,C3,C4,C5,C6,C7,C8,C9,E1,E2,D1,D2,S1,S2}opcionMenu;

int bandera1=0, bandera2=0;
int luz=1;

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
  float eyeX=-10.0f, eyeY=0.0f, eyeZ=0.0f;
  float oriX=0.0f, oriY=1.0f, oriZ=0.0f;

    //variables globales para el cálculo de los grados
	int x0, y0;


void luzAmbiental(void)
{
	GLfloat l_difusa[]={ 0.780392f, 0.568627f, 0.113725f, 1.0f };
	GLfloat l_especular[]={ 0.992157f, 0.941176f, 0.807843f, 1.0f };
	GLfloat l_posicion[]={1.0, 1.0, 1.0, 0.0};

	GLfloat l_ambiente[]={ 0.329412f, 0.223529f, 0.027451f,1.0f };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,l_ambiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambiente);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);

	glEnable (GL_LIGHT0);
}

void luzAmbiental2(void)
{
	GLfloat l_difusa[]={ 0.50754f, 0.50754f, 0.50754f, 1.0f};
	GLfloat l_especular[]={0.508273f, 0.508273f, 0.508273f, 1.0f };

	GLfloat l_posicion[]={1.0, 1.0, 1.0, 0.0};

	GLfloat l_ambiente[]={ 0.19225f, 0.19225f, 0.19225f, 1.0f };


    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,l_ambiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambiente);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);

	glEnable (GL_LIGHT0);
}



void init(void)
{

if(luz==0){
  glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
	luzAmbiental();
	glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}else{
  glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
  luzAmbiental2();
	glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

}

void cubo(){
    const float sizex = 4.0f;
    const float sizey = 4.0f;
    const float sizez = 4.0f;

    glBegin(GL_QUADS);

  //  glColor3f(1.0, 1.0, 0.0);

    // FRONT
    glNormal3f(0.0,0.0,1);
    glVertex3f(-sizex, -sizey, sizez);
    glVertex3f(sizex, -sizey, sizez);
    glVertex3f(sizex, sizey, sizez);
    glVertex3f(-sizex, sizey, sizez);

    // BACK
    glNormal3f(0.0,0.0,1);
    glVertex3f(-sizex, -sizey, -sizez);
    glVertex3f(-sizex, sizey, -sizez);
    glVertex3f(sizex, sizey, -sizez);
    glVertex3f(sizex, -sizey, -sizez);

    //glColor3f(0.0, 1.0, 0.0);

    // LEFT
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-sizex, -sizey, sizez);
    glVertex3f(-sizex, sizey, sizez);
    glVertex3f(-sizex, sizey, -sizez);
    glVertex3f(-sizex, -sizey, -sizez);

    // RIGHT
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(sizex, -sizey, -sizez);
    glVertex3f(sizex, sizey, -sizez);
    glVertex3f(sizex, sizey, sizez);
    glVertex3f(sizex, -sizey, sizez);

    glColor3f(0.0, 0.0, 1.0);

    // TOP
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-sizex, sizey, sizez);
    glVertex3f(sizex, sizey, sizez);
    glVertex3f(sizex, sizey, -sizez);
    glVertex3f(-sizex, sizey, -sizez);

    // BOTTOM
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-sizex, -sizey, sizez);
    glVertex3f(-sizex, -sizey, -sizez);
    glVertex3f(sizex, -sizey, -sizez);
    glVertex3f(sizex, -sizey, sizez);

    glEnd();

}


//Piramide
void pyramid()
{
  //limpiamos pantalla
// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//inicio de dibujo de un cuadrado

//-----base de la piramide--varios colores
//se usa GL_QUADS para crear un cuadrilátero
glBegin(GL_QUADS);
//vértices en 3d
//glColor3f(0,0,0);//rojo
glVertex3d(-4,0,-4);//4
glVertex3d(-4,0,4);//3
glVertex3d(4,0,4);//2
glVertex3d(4,0,-4);//1
glEnd();
//------------------caras de la pirámide
//para las caras triangulares
//se usará GL_TRIANGLES
//--------Cara 4  amarillo con blanco
glBegin(GL_TRIANGLES);
//vértices en 3d
//glColor3f(1,0,0);//blanco
glVertex3d(0,4,0);
glVertex3d(-4,0,-4);//1
glVertex3d(4,0,-4);//4
glEnd();

//--------Cara 1 rojo con blanco
glBegin(GL_TRIANGLES);
//vértices en 3d
//glColor3f(0,1,0);//blanco
glVertex3d(0,4,0);
glVertex3d(4,0,-4);
glVertex3d(4,0,4);
glEnd();
//--------Cara 3 verde con blanco
glBegin(GL_TRIANGLES);
//vértices en 3d
//glColor3f(0,0,1);//blanco
glVertex3d(0,4,0);
glVertex3d(-4,0,4);
glVertex3d(-4,0,-4);
glEnd();
//-------Cara 2 azul con blanco
glBegin(GL_TRIANGLES);
//vértices en 3d
//glColor3f(1,1,0);//blanco
glVertex3d(0,4,0);
glVertex3d(4,0,4);
glVertex3d(-4,0,4);
glEnd();
glFlush();
//cambio del bufer oculto al activo
//glutSwapBuffers();

}

void display2(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  gluPerspective(45.0f, 1.0, 5.0f, -5.0f);
  	gluLookAt(0.0f, 0.0f, 10.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
  glEnable(GL_CULL_FACE);
	glLoadIdentity();

  if(luz==0){
    glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
  	luzAmbiental();
  	glEnable(GL_LIGHTING);
      glEnable(GL_DEPTH_TEST);
  	glDepthFunc(GL_LEQUAL);
  }else{
    glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
    luzAmbiental2();
  	glEnable(GL_LIGHTING);
      glEnable(GL_DEPTH_TEST);
  	glDepthFunc(GL_LEQUAL);
  }



	glPushMatrix();
		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);
    glScalef(1/2.0,1/2.0,1/2.0);


    //Cola trasera
       glPushMatrix();
        glScalef(1/4.5,1/4.5,1/4.5);
        glScalef(2,1,0.05);
        glTranslatef(0,30,1);
        glRotatef(90,0.0,0.0,1.0);
        glColor3f(1.0,0.0,0.0);
        cubo();
       glPopMatrix();



    //Cola trasera
       glPushMatrix();
        glScalef(1/4.5,1/4.5,1/4.5);
        glScalef(2,1,0.1);
        glScalef(1,5,1);
        glRotatef(45,0.0,0.0,1.0);
        glColor3f(0.0,0.0,0.0);
        cubo();
       glPopMatrix();

   //Cola de avion
   glPushMatrix();
    glScalef(1/4.0,1/4.0,1/4.0);
    glScalef(1, 4, 1);
    glColor3f(1.0,0.0,0.0);
    pyramid();
   glPopMatrix();

   //Ala principal
      glPushMatrix();
       glScalef(1/4.0,1/4.0,1/4.0);
       glScalef(5,1,0.1);
       glColor3f(1.0,0.0,0.0);
       cubo();
      glPopMatrix();

   //alas de avion
   glPushMatrix();
    glScalef(1/4.5,1/4.5,1/4.5);
    glColor3f(1.0,0.0,0.0);
    cubo();
   glPopMatrix();


   //punta avion
    glPushMatrix();
    glScalef(1/4.0,1/4.0,1/4.0);
    glScalef(1, -1, 1);
    glScalef(1, 3, 1);
    // glTranslatef(1,0.5,0.5);
    glColor3f(1.0,0.0,0.0);
    pyramid();
    glPopMatrix();

	glPopMatrix();
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			// eyeX=0.0f, eyeY=0.0f, eyeZ=5.0f;
			// oriX=0.0f, oriY=1.0f, oriZ=0.0f;
     luz=0;
      break;
		case F2:
      luz=1;
			//Trasera
			// eyeX=0.0f, eyeY=5.0f, eyeZ=1.0f;
			// oriX=0.0f, oriY=1.0f, oriZ=0.0f;
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
	glutAddMenuEntry("Brass", F1);
	//glutAddMenuEntry("Trasera", F2);
	glutAddMenuEntry("Silver", F2);


	menuMain = glutCreateMenu(menuPosicionCamara);
    glutAddSubMenu("Materiales", menuCAMARA);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}




int main(int argc, char *argv[])
{
	glutInit( & argc, argv );
  //inicio del boblebuffering para evitar parpadeo
glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(615, 100);
	glutCreateWindow("AVION");
	init();
  creacionMenu();
  glutDisplayFunc(display2);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);

	glutMainLoop();

	return 0;
}
