#include <GL/glut.h>
/*  Practica 1 - Actividad 1
Probar que la instalación esté correcta probando
el ejemplo adjunto al manual.
*/
void dibujar(){
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(-1.0f,-1.0f,0.0f);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f,1.0f,0.0f);
glEnd();
glFlush();
}


int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutCreateWindow("OpenGL Test");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(dibujar);
   glutMainLoop();
   return 0;
}
