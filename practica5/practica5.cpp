#include <GL/glut.h>
#include <stdio.h>
/*
Practica 5

1. Descargar codigo de ejemplo
2. Agregar a la matriz de colores los colores amarillo, magneta, cian, gris, Negro
3.Usar la matriz de colores para modificar automaticamente el valor de las
luces difusa y especula
4.Observar la estructura de las funciones luz ambiental y de luzuno(), crear una segunda luzDOs()
pero modificar los arreglos l_difusa y l_especular
5.Modificar el glClearColor() que se encuentra dentro de la funcion display()
para que se pueda modificar el fondo desde el menu, utilizando la matriz
ce colores previamente definida
7. Usar los enumerados opcionMenu y programar la funcion menuFiguras
8.Invocar a la funcion luzDos();
9 vreficar comportamiento y funcionamiento de ControlTeclado();
10. Prueba cambiando el color de una figura
11. ahora pruebacambiando el color desde la funcion de luzAmbiental();


*/


int sky=1;
	//Matriz de colores
	float colores[10][3]=
	{
        { 1.00f, 1.00f, 1.00f}, // 0 - blanco
        { 0.00f, 0.00f, 0.00f}, // 1 - negro
	    {1.0,1.0,0.0}, //2 amarillo
		{1.0,0.0,1.0}, //3 magenta
		{0.0,1.0,1.0}, //4 cian
		{0.5,0.5,0.5}, //5 gris
		{0.0,0.0,1.0},//6 azul
		{0.5,0.0,0.5}, //7 purpura
		{0.0,0.5,0.0}, //8 verde
		{0.78,0.082,0.5215} // 9violeta
	};

	int color  = 0;     // color de FIGURA
	int colorf = 0;     // color de FONDO
	int colorl = 2;     // color de LUZ
	int colorl2 =0;
	int b=0,b2=0;


	//variables globales para la rotacion
	float alpha, beta;
	int x0, y0;
	int opc;

	//Variables globales para las transformaciones
	float xpos=0, ypos=0, inc=0.5;

	//Menu de figuras a elegir
	typedef enum{F1,F2,F3,F4,F5,F6,F7,F8,F9,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,E1,E2,D1,D2,S1,S2,FONDO0,FONDO1}opcionMenu;

void luzAmbiental(void)
{
	//GLfloat l_difusa[]={1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat l_difusa[]={colores[color][0], colores[color][1], colores[color][2], 0.0f};
	GLfloat l_especular[]={colores[color][0], colores[color][1], colores[color][2]};
	GLfloat l_posicion[]={0.0, 0.0, 5.0, 1.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
	glEnable (GL_LIGHT0);
}

void luzUno(void)
{
    if(b==1){

	//GLfloat l_difusa[]={colores[2][0], colores[2][0], colores[2][0], 0.0f};
    GLfloat l_difusa[]={colores[colorl2][0], colores[colorl2][1], colores[colorl2][2], 0.0f};
	//GLfloat l_difusa[]={1.0f, 1.0f, 1.0f, 0.0f};
	GLfloat l_especular[]={colores[3][0], colores[3][1], colores[4][2], 0.0f};
	GLfloat l_posicion[]={0.0f, 5.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
	glEnable (GL_LIGHT1);

    }else{
        //GLfloat l_difusa[]={colores[2][0], colores[2][0], colores[2][0], 0.0f};
    GLfloat l_difusa[]={colores[color][0], colores[color][1], colores[color][2], 0.0f};
	//GLfloat l_difusa[]={1.0f, 1.0f, 1.0f, 0.0f};
	GLfloat l_especular[]={colores[3][0], colores[3][1], colores[4][2], 0.0f};
	GLfloat l_posicion[]={0.0f, 5.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
	glEnable (GL_LIGHT1);


    }

}

void luzDos(void)
{
    if(b2==1){
        GLfloat l_difusa[]={colores[colorl][0], colores[colorl][1], colores[colorl][2], 0.0f};
	//GLfloat l_difusa[]={0.0f, 0.5f, 0.0f, 0.0f};
	GLfloat l_especular[]={colores[3][0], colores[3][1], colores[4][2], 0.0f};
	GLfloat l_posicion[]={0.0f, 1.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
	  glEnable (GL_LIGHT1);
    }else{
        GLfloat l_difusa[]={colores[color][0], colores[color][1], colores[color][2], 0.0f};
	//GLfloat l_difusa[]={0.0f, 0.5f, 0.0f, 0.0f};
	GLfloat l_especular[]={colores[3][0], colores[3][1], colores[4][2], 0.0f};
	GLfloat l_posicion[]={0.0f, 5.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
	  glEnable (GL_LIGHT1);
    }


}
void luzTres(void)
{
	GLfloat l_difusa[]={colores[2][0], colores[4][1], colores[5][5], 0.0f};
	GLfloat l_especular[]={colores[3][5], colores[5][2], colores[4][2], 0.0f};

	GLfloat l_posicion[]={0.0, 0.0, 0.0, 1.0};
	GLfloat spot_direccion[]={0.0, 0.0, 0.0, 0.0};

	glLightfv(GL_LIGHT3, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT3, GL_POSITION, l_posicion);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direccion);
	//glEnable (GL_LIGHT3);
}

void init(void)
{

     glEnable(GL_CULL_FACE);
	 luzAmbiental();
	 //luzUno();
	 glEnable(GL_LIGHTING);
	 glEnable(GL_DEPTH_TEST);

	//  mciSendString("open Datos/Sonido.mp3 type sequencer", NULL, 0, NULL);
	//  mciSendString("play Datos/Sonido.mp3", NULL, 0, NULL);

}

void display(void)
{
    glClearColor(colores[sky][0], colores[sky][1], colores[sky][2], 0.0);

	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	gluLookAt(0.0f, 0.0f, 5.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

		glTranslatef(xpos,ypos,0);

		if(opc != 9)
			glScalef(inc,inc,inc);
		else
			glScalef(inc-0.15,inc-0.15,inc-0.15);

		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);

		//glColor3f(0.5f, 0.5f, 0.5f);

		switch(opc)
		{
			case 1:
				glutSolidCube(0.5);
				break;
            case 2:
                glutWireCube(1.0);
                break;
            case 3:
                glPushMatrix();
                glScaled(2.5,2.5,2.5);
                glutSolidTorus(0.10,0.15,15,15);
                glPopMatrix();
                break;
            case 4:
                glPushMatrix();
                glScaled(3.0,3.0,3.0);

                glutWireTorus(0.20,0.30,10,30);
                glPopMatrix();
                break;
            case 5:
                glPushMatrix();
                glScaled(2.5,2.5,2.5);
                glutSolidSphere(0.2,30,30);
                glPopMatrix();
                break;
            case 6:
                glPushMatrix();
                glScaled(2.5,2.5,2.5);
                glutWireSphere(0.2, 15, 15);
                glPopMatrix();
                break;
            case 7:
                glPushMatrix();
                glScaled(1,1,1);
                glutSolidDodecahedron();
                glPopMatrix();
                break;
            case 8:
                //glPushMatrix();
                //glScaled(2.5,2.5,2.5);
                glutSolidOctahedron();
                //glPopMatrix();
                break;
            case 9:
                glPushMatrix();
                glScaled(2.5,2.5,2.5);
                glutSolidCone(0.2,0.4,15,15);
                glPopMatrix();
                break;

		}

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

void menuFiguras(int opcion)
{
	switch(opcion)
	{
		case F1:
			opc=1;
			break;
        case F2:
			opc=2;
			break;
        case F3:
            opc=3;
            break;
        case F4:
            opc=4;
            break;
        case F5:
            opc=5;
            break;
        case F6:
            opc=6;
            break;
        case F7:
            opc=7;
            break;
        case F8:
            opc=8;
            break;
        case F9:
            opc=9;
            break;
        case FONDO0:
			sky = 0;
			break;
		case FONDO1:
			sky = 1;
			break;
        case C1:
            color=0;
            break;
        case C2:
            color=1;
            break;
        case C3:
            color=2;
            break;
        case C4:
            color=3;
            break;
        case C5:
            color=4;
            break;
        case C6:
            color=5;
            break;
        case C7:
            color=6;
            break;
        case C8:
            color=7;
            break;
        case C9:
            color=8;
            break;
        case C10:
            color=9;
            break;
        case E1:
            b=1;
            break;
        case E2:
            b2=1;

            break;
        case D1:
            b=0;
            break;
        case D2:
            b2=0;
            break;
		//case E1:
			//glEnable(GL_LIGHT1);
			//break;
	}

	luzAmbiental();
	luzUno();
	luzDos();
	//luzTres();

	glutPostRedisplay();
}

//Creacion de menu y submenus
void creacionMenu(void)
{
	int menuFIGURA, menuFONDO, menuCOLOR, menuLUCES, menuMain;
	int on, off;

    //----------------------------------------------------------

    // NIVEL 2 DE SUB-MENU PARA TIPO DE FIGURA
	menuFIGURA = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Cube", F1);
	glutAddMenuEntry("Cubo Alambres",F2);
	glutAddMenuEntry("Dona Solida", F3);
	glutAddMenuEntry("Dona Alambres", F4);
	glutAddMenuEntry("Esfera Solida", F5);
	glutAddMenuEntry("Esfera Alambres", F6);
	glutAddMenuEntry("Dodecaedro Solido", F7);
	glutAddMenuEntry("Octaedro Solido", F8);
	glutAddMenuEntry("Cono Solido", F9);




	/*
        AQUI VAN LAS OPCIONES
    */

	//----------------------------------------------------------

    // NUVEL 2 DE SUB-MENU PARA COLOR DE FONDO
	menuFONDO = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Blanco", FONDO0);
	glutAddMenuEntry("Negro", FONDO1);
	/*
        AQUI VAN LAS OPCIONES
    */

	//----------------------------------------------------------

        // NIVEL 3 DE SUB-MENUS PARA ACTIVAR LUCES
        on = glutCreateMenu(menuFiguras);
        glutAddMenuEntry("Luz uno", E1);
        glutAddMenuEntry("Luz dos", E2);
        /*
            AQUI VAN LAS OPCIONES
        */

        // NIVEL 3 DE SUB-MENUS PARA DESACTIVAR LUCES
        off = glutCreateMenu(menuFiguras);
        glutAddMenuEntry("Luz uno", D1);
        glutAddMenuEntry("Luz dos", D2);
        /*
            AQUI VAN LAS OPCIONES
        */

    // NIVEL 2 DE SU-MENUS
	menuLUCES = glutCreateMenu(menuFiguras);
	glutAddSubMenu("Activar", on);
	glutAddSubMenu("Desactivar",off);
	/*
        AQUI VAN LOS SUB-MENUS DE NIVEL 3
    */

	//----------------------------------------------------------

    // NIVEL 2 DE SUB-MENUS
	menuCOLOR = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Blanco", C1);
	glutAddMenuEntry("Negro", C2);
	glutAddMenuEntry("Amarillo", C3);
	glutAddMenuEntry("Magenta", C4);
	glutAddMenuEntry("Cian", C5);
	glutAddMenuEntry("Gris", C6);
	glutAddMenuEntry("Azul", C7);
	glutAddMenuEntry("Purpura", C8);
	glutAddMenuEntry("Verde", C9);
	glutAddMenuEntry("Violeta", C10);

	/*
        AQUI VAN LAS OPCIONES
    */

    // MENU PRINCIPAL (NIVEL 1)
	menuMain = glutCreateMenu(menuFiguras);
    glutAddSubMenu("Figura", menuFIGURA);
    glutAddSubMenu("Fondo", menuFONDO);
    glutAddSubMenu("Color", menuCOLOR);
    glutAddSubMenu("Luces", menuLUCES);
	/*
        AQUI VAN LOS SUB-MENUS DE NIVEL 2
    */

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ControlTeclado(int Key, int x, int y)
{
	switch(Key)
	{
		//TRASLACION
		case GLUT_KEY_RIGHT:
			xpos+=0.05;
			break;
		case GLUT_KEY_LEFT:
			xpos-=0.05;
			break;
		case GLUT_KEY_UP:
			ypos+=0.05;
			break;
		case GLUT_KEY_DOWN:
			ypos-=0.05;
			break;
		//ESCALAMIENTO
		case GLUT_KEY_HOME:
			inc+=0.05;
			break;
		case GLUT_KEY_END:
			if(inc > 0.0)
				inc-=0.05;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Figuras 3D");
	init();
//	sndPlaySoundW("C:\\Windows\\Media\\Alarm01.wav",0);
	glutDisplayFunc(display);
	glutSpecialFunc(ControlTeclado);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	creacionMenu();
	glutMainLoop();
	return 0;
}
