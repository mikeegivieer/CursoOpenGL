#include <GL/glut.h>

#include <assert.h>
#include <fstream>

using namespace std;



//************************************+
// Funciones para la Carga de las Texturas
//Represents an image

class Image {
	public:
		Image(char* ps, int w, int h);
		~Image();
		char* pixels;
		int width;
		int height;
};

//Reads a bitmap image from file.
Image* loadBMP(const char* filename);

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {

}

Image::~Image() {
	delete[] pixels;
}

namespace {
	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}

	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}

	//Reads the next four bytes as an integer, using little-endian form
	int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}

	//Reads the next two bytes as a short, using little-endian form
	short readShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}

	//Just like auto_ptr, but for arrays
	template<class T>
	class auto_array {
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false) {
			}

			auto_array(const auto_array<T> &aarray) {
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			~auto_array() {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
			}

			T* get() const {
				return array;
			}

			T &operator*() const {
				return *array;
			}

			void operator=(const auto_array<T> &aarray) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			T* operator->() const {
				return array;
			}

			T* release() {
				isReleased = true;
				return array;
			}

			void reset(T* array_ = NULL) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = array_;
			}

			T* operator+(int i) {
				return array + i;
			}

			T &operator[](int i) {
				return array[i];
			}
	};
}

Image* loadBMP(const char* filename) {
	ifstream input;
	input.open(filename, ifstream::binary);
	assert(!input.fail() || !"Could not find file");
	char buffer[2];
	input.read(buffer, 2);
	assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
	input.ignore(8);
	int dataOffset = readInt(input);

	//Read the header
	int headerSize = readInt(input);
	int width;
	int height;
	switch(headerSize) {
		case 40:
			//V3
			width = readInt(input);
			height = readInt(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			assert(readShort(input) == 0 || !"Image is compressed");
			break;
		case 12:
			//OS/2 V1
			width = readShort(input);
			height = readShort(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			break;
		case 64:
			//OS/2 V2
			assert(!"Can't load OS/2 V2 bitmaps");
			break;
		case 108:
			//Windows V4
			assert(!"Can't load Windows V4 bitmaps");
			break;
		case 124:
			//Windows V5
			assert(!"Can't load Windows V5 bitmaps");
			break;
		default:
			assert(!"Unknown bitmap format");
	}

	//Read the data
	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels(new char[size]);
	input.seekg(dataOffset, ios_base::beg);
	input.read(pixels.get(), size);

	//Get the data into the right format
	auto_array<char> pixels2(new char[width * height * 3]);
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			for(int c = 0; c < 3; c++) {
				pixels2[3 * (width * y + x) + c] =
					pixels[bytesPerRow * y + 3 * x + (2 - c)];
			}
		}
	}

	input.close();
	return new Image(pixels2.release(), width, height);
}

// FIN DE LAS FUNCIONES PARA CARGAR TEXTURAS ....
//

const float BOX_SIZE = 4.0f; //The length of each side of the cube
float Angulo = 0;            //The rotation of the box
GLuint ID_de_Textura1;           //The OpenGL id of the texture
GLuint ID_de_Textura2;           //The OpenGL id of the texture
GLuint ID_de_Textura3;
GLuint ID_de_Textura4;
GLuint ID_de_Textura5;
GLuint ID_de_Textura6;



//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);

	Image* image1 = loadBMP("wood.bmp");
	Image* image2 = loadBMP("wood.bmp");
	Image* image3 = loadBMP("wood.bmp");
	Image* image4 = loadBMP("wood.bmp");
	Image* image5 = loadBMP("wood.bmp");
	Image* image6 = loadBMP("wood.bmp");
	ID_de_Textura1 = loadTexture(image1);
	ID_de_Textura2 = loadTexture(image2);
	ID_de_Textura3 = loadTexture(image3);
	ID_de_Textura4 = loadTexture(image4);
	ID_de_Textura5 = loadTexture(image5);
	ID_de_Textura6 = loadTexture(image6);

	delete image1,image2,image3,image4,image5,image6;
}


//***************************

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
	// GLfloat l_difusa[]={ 0.780392f, 0.568627f, 0.113725f, 1.0f };
	// GLfloat l_especular[]={ 0.992157f, 0.941176f, 0.807843f, 1.0f };
	// GLfloat l_posicion[]={1.0, 1.0, 1.0, 0.0};
	// GLfloat l_ambiente[]={ 0.329412f, 0.223529f, 0.027451f,1.0f };

  //   glLightModelfv(GL_LIGHT_MODEL_AMBIENT,l_ambiente);
  //   glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambiente);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	// glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
	// glEnable (GL_LIGHT0);

  GLfloat l_difusa[]={0.5f, 0.5f, 0.5f, 0.0f};
  	GLfloat l_especular[]={0.5f, 0.5f, 0.5f, 0.0f};
  	GLfloat l_posicion[]={0.0, 0.0, 5.0, 1.0};

  	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
  	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
  	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
  	//glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
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
glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void cubo(){
    const float sizex = 4.0f;
    const float sizey = 4.0f;
    const float sizez = 4.0f;


  //  glColor3f(1.0, 1.0, 0.0);
  glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, ID_de_Textura1);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glBegin(GL_QUADS);

     glColor3f(1.0, 1.0, 0.0);
     // FRONT
     glNormal3f(0.0,0.0,1);
     glVertex3f(-sizex, -sizey, sizez);
     glTexCoord2f(0.0f, 0.0f);
     glVertex3f(sizex, -sizey, sizez);
     glTexCoord2f(1.0f, 0.0f);
     glVertex3f(sizex, sizey, sizez);
     glTexCoord2f(1.0f, 1.0f);
     glVertex3f(-sizex, sizey, sizez);
     glTexCoord2f(0.0f, 1.0f);
     glDisable(GL_TEXTURE_2D);
     // BACK

     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, ID_de_Textura1);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glNormal3f(0.0,0.0,1);
     glVertex3f(-sizex, -sizey, -sizez);
     glTexCoord2f(0.0f, 0.0f);
     glVertex3f(-sizex, sizey, -sizez);
     glTexCoord2f(1.0f, 0.0f);
     glVertex3f(sizex, sizey, -sizez);
     glTexCoord2f(1.0f, 1.0f);
     glVertex3f(sizex, -sizey, -sizez);
     glTexCoord2f(0.0f, 1.0f);
     glDisable(GL_TEXTURE_2D);

     glColor3f(0.0, 1.0, 0.0);

     // LEFT

     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, ID_de_Textura1);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glNormal3f(1.0,0.0,0.0);
     glVertex3f(-sizex, -sizey, sizez);
     glTexCoord2f(0.0f, 0.0f);
     glVertex3f(-sizex, sizey, sizez);
         glTexCoord2f(1.0f, 0.0f);
     glVertex3f(-sizex, sizey, -sizez);
     glTexCoord2f(1.0f, 1.0f);
     glVertex3f(-sizex, -sizey, -sizez);
     glTexCoord2f(0.0f, 1.0f);
     glDisable(GL_TEXTURE_2D);



     // RIGHT
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, ID_de_Textura1);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glNormal3f(1.0,0.0,0.0);
     glVertex3f(sizex, -sizey, -sizez);
     glTexCoord2f(0.0f, 0.0f);
     glVertex3f(sizex, sizey, -sizez);
     glTexCoord2f(1.0f, 0.0f);
     glVertex3f(sizex, sizey, sizez);
     glTexCoord2f(1.0f, 1.0f);
     glVertex3f(sizex, -sizey, sizez);
     glTexCoord2f(0.0f, 1.0f);
     glDisable(GL_TEXTURE_2D);

     glColor3f(0.0, 0.0, 1.0);

     // TOP
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, ID_de_Textura1);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glNormal3f(0.0,1.0,0.0);
     glVertex3f(-sizex, sizey, sizez);
     glTexCoord2f(0.0f, 0.0f);
     glVertex3f(sizex, sizey, sizez);
     glTexCoord2f(1.0f, 0.0f);
     glVertex3f(sizex, sizey, -sizez);
     glTexCoord2f(1.0f, 1.0f);
     glVertex3f(-sizex, sizey, -sizez);
      glTexCoord2f(0.0f, 1.0f);
      glDisable(GL_TEXTURE_2D);

     // BOTTOM
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, ID_de_Textura1);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glNormal3f(0.0,1.0,0.0);
     glVertex3f(-sizex, -sizey, sizez);
     glTexCoord2f(0.0f, 0.0f);
     glVertex3f(-sizex, -sizey, -sizez);
     glTexCoord2f(1.0f, 0.0f);
     glVertex3f(sizex, -sizey, -sizez);
     glTexCoord2f(1.0f, 1.0f);
     glVertex3f(sizex, -sizey, sizez);
     glTexCoord2f(0.0f, 1.0f);
     glDisable(GL_TEXTURE_2D);
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
  initRendering();
  creacionMenu();
  glutDisplayFunc(display2);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);

	glutMainLoop();

	return 0;
}
