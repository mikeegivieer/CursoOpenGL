
#include <GL/glut.h>

/*   Practica 1 - Actividad 2
1. Usar como base el código 01_ejemplo1.cpp, desponible como archivo adjunto

2. Dibujar en la misma ventana una figura convexa por cada
una de las siguiente primitivas de OpenGL
GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES, GL_POLYGON

3.Indicarle a OpenGL que solo muestre la cara frontal de las primitivas
dibujadas y que se visualicen en modo alambre usando la funcion glPolygonMode();

4. Asignar un color diferente usando glColor3f() a cada conjunto de vertices
dibujados entre cada glBgin() y glEnd()

5. Sabiendo que OpenGL es considerada una maquina de estados y que la funcion
main() administra las funciones principales para visualizar todo en una ventana
que parte del código de la funcion main() tendrias que repetir para generar
una nueva ventana con las siguientes caracteristicas:
Mismo modo de display
Mismas medidas
Misma posicion en x y
Nombre igual a "Mi segundo ejemplo"

6. Sin importar si se trata de un numero par o impar de vertices, dibujar en
otra ventana (mismo programa) las siguientes primitivas
GL_LINE_STRIP, GL_TRIANGLE_FAN, GL_QUADS, GL_QUADS_STRIP

7. Considerar el orden de los vertices para conservar un sentido antihorario

8. Para el caso de los triangulos, cuadrados y poligonos, probar el modo de visualizacion
para que la figura sea en modo relleno (GL_FILL)
*/

void init(void)
{
	glPolygonMode(GL_FRONT,GL_FILL);          //PROBANDO MODO DE RELLENO GL_FILL
	//glPolygonMode(GL_FRONT,GL_LINE);        //CARA FRONTAL Y SE VISUALIZAN EN MODO ALAMBRE
	glClearColor(1.0, 1.0, 1.0, 0.0);       // DEFINE COLOR DE FONDO
	glColor3f(0.0f, 0.0f, 1.0f);            // DEFINE COLOR DE PUNTOS
	glPointSize(8.0);                       // DEFINE TAMAÑO DE PUNTO
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);     // DEFINE VISTA (ORTOGONAL 2D)
}

void figura1_GL_POINTS(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   // LIMPIA PANTALLA
  glColor3f(1.0f, 0.0f, 0.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_POINTS);
	  glVertex2i(200, 300);
    for (int x=0; x<=100; x+=10){
    glVertex2i(200+x, 300);
    }
    for (int x=0; x<=100; x+=10){
    glVertex2i(300, 300-x);
    }
    for (int x=0; x<=100; x+=10){
    glVertex2i(300-x, 200);
    }
    for (int x=0; x<=100; x+=10){
    glVertex2i(200, 200+x);
    }
    glEnd();
	glFlush();
}

void figura2_GL_LINES(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 1.0f, 0.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_LINES);
      glVertex3f(200.0f,300.0f,0.0f);
      glVertex3f(500.0f,300.0f,0.0f);

      glVertex3f(500.0f,300.0f,0.0f);
      glVertex3f(200.0f,100.0f,0.0f);

			glVertex3f(200.0f,100.0f,0.0f);
			glVertex3f(200.0f,300.0f,0.0f);
    glEnd();

	glFlush();
}


void figura3_GL_LINE_STRIP(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0f, 1.0f, 0.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_LINE_STRIP);

      glVertex3f(200.0f,400.0f,0.0f);
      glVertex3f(500.0f,400.0f,0.0f);
      glVertex3f(500.0f,100.0f,0.0f);
      glVertex3f(200.0f,100.0f,0.0f);
			glVertex3f(200.0f,400.0f,0.0f);

    glEnd();

	glFlush();
}

void figura4_GL_LINE_LOOP(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 1.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_LINE_LOOP);

      glVertex3f(100.0f,300.0f,0.0f);
      glVertex3f(500.0f,300.0f,0.0f);
      glVertex3f(500.0f,50.0f,0.0f);
      glVertex3f(100.0f,50.0f,0.0f);

    glEnd();

	glFlush();
}
void figura5_GL_TRIANGLES(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 1.0f);    // COLOR DE LOS TRAZOS
  glBegin(GL_TRIANGLES);
      glVertex3f(200.0f,300.0f,0.0f);
      glVertex3f(300.0f,300.0f,0.0f);
      glVertex3f(200.0f,200.0f,0.0f);
      glVertex3f(300.0f,300.0f,0.0f);
      glVertex3f(200.0f,200.0f,0.0f);
      glVertex3f(300.0f,200.0f,0.0f);
    glEnd();
	glFlush();
}

void figura6_GL_POLYGON(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0f, 1.0f, 1.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_POLYGON);
      glVertex3f(200.0f,300.0f,0.0f);
      glVertex3f(500.0f,300.0f,0.0f);
      glVertex3f(500.0f,100.0f,0.0f);
      glVertex3f(200.0f,100.0f,0.0f);

    glEnd();

	glFlush();
}

//------------------- FIGURAS PARA LA SEGUNDA VENTANA -------------

void figura7_GL_TRIANGLE_STRIP(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0f, 0.0f, 0.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(200.0f,300.0f,0.0f);
      glVertex3f(500.0f,50.0f,0.0f);
      glVertex3f(400.0f,200.0f,0.0f);
    glEnd();

	glFlush();
}

void figura8_GL_TRIANGLE_FAN(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0f, 1.0f, 0.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_TRIANGLE_FAN);
      glVertex3f(200.0f,300.0f,0.0f);
      glVertex3f(500.0f,300.0f,0.0f);
      glVertex3f(300.0f,100.0f,0.0f);

    glEnd();

	glFlush();
}

void figura9_GL_QUADS(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0f, 0.0f, 1.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_QUADS);
      glVertex3f(200.0f,300.0f,0.0f);
      glVertex3f(500.0f,300.0f,0.0f);
      glVertex3f(500.0f,100.0f,0.0f);
      glVertex3f(200.0f,100.0f,0.0f);

    glEnd();

	glFlush();
}

void figura10_GL_QUADS_STRIP(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0f, 0.0f, 1.0f);    // COLOR DE LOS TRAZOS
	glBegin(GL_QUAD_STRIP);
      glVertex3f(200.0f,300.0f,0.0f);
      glVertex3f(500.0f,300.0f,0.0f);
      glVertex3f(500.0f,100.0f,0.0f);
      glVertex3f(200.0f,100.0f,0.0f);
			glVertex3f(400.0f,300.0f,0.0f);
      glVertex3f(300.0f,300.0f,0.0f);

    glEnd();

	glFlush();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Mi primer ejemplo");
    glutDisplayFunc(figura1_GL_POINTS);
    init();

		/*

		La fincion que tengo que cambiar para generar
		"mi segundo ejemplo" es glutCreateWindow("Mi segundo ejemplo");
*/


		glutInitWindowSize(500, 500);
		glutInitWindowPosition(50, 50);
		glutCreateWindow("Mi segundo ejemplo");
		glutDisplayFunc(figura8_GL_TRIANGLE_FAN);
		init();
		glutMainLoop();

}
