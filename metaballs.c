/*
 * Mataballs on PSP
 *
 * gloob / TsT
 *
 * $Id$
 *
 */

#include <stdlib.h>

#include "gl.h"

#include "particle.h"

#ifdef __PSP__
  #define SCREEN_WIDTH 480
  #define SCREEN_HEIGHT 272
#else
  #define SCREEN_WIDTH 800
  #define SCREEN_HEIGHT 600
#endif

static GLboolean rotateX = GL_FALSE;
static GLboolean rotateY = GL_FALSE;
static GLboolean rotateZ = GL_FALSE;

static GLfloat deltaX = 0.0f;
static GLfloat deltaY = 0.0f;
static GLfloat deltaZ = -75.0f;

static unsigned char index = 0;

static cube cube0;
static particle particles[1];
static float isovalue = 100.0f;

static void setupGL(int w, int h)
{
	
	GLfloat fAspect;

	// I eat zero division as breakfast...:]
	if(h == 0) 
		h = 1;

	// Relación de aspecto de la ventana (Aspect Ratio)
	fAspect = (GLfloat) w / (GLfloat) h;
	
	// Define una vista con las dimensiones h y w.
	glViewport( 0, 0, w, h );

	// Selecciona el sistema de coordenadas en perspectiva...
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	// ...y definir el campo de visualización.
	// 60º, plano proximo = 1.0 plano lejano = 425
	gluPerspective( 45.0f, fAspect, 0.1f, 200.0f );
	// Modelo de sombreado.
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glShadeModel( GL_SMOOTH );
	// Color de borrado.
	glClearColor( 0.0f, 0.0f, 0.2f, 1.0f);
	glClearDepth( 1.0f );

	// Desactivar test de profundidad.
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_CULL_FACE );
	//glFrontFace ( GL_CW );

	// Activar el Blending.
//	glEnable( GL_BLEND );
//	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
//	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	// Color de pincel.
	glColor3f( 1.0f, 0.0f, 0.0f );

		// PIXELS DEFINITIONS!!
	//Definir tamaño del punto.
	//glPointSize( 3.0f );
    // Activar "antialiasing" de puntos
//	glEnable( GL_POINT_SMOOTH );
}

static
void reshape (int w, int h)
{
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void display() {

	//glRotatef(angle * 1.32f, 0.0f, 0.0f, 1.0f)
	
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();
}

static void display2() {

	static GLfloat xRot = 0.0f, yRot = 0.0f, zRot = 0.0f;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/* We don't want to modify the projection matrix. */
 //   glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    /* Move down the z-axis. */
    glTranslatef( deltaX, deltaY, deltaZ );

    if( rotateX ) {
        //xRot += 45.0f;
		if( ++xRot > 360.0f ) {
            xRot = 0.0f;
        }
		//rotateX = !rotateX;
    }

    if( rotateY ) {
        //yRot += 45.0f;
		if( ++yRot > 360.0f ) {
            yRot = 0.0f;
        }
		//rotateY = !rotateY;
    }

    if( rotateZ ) {
		//zRot += 45.0f;
        if( ++zRot > 360.0f ) {
            zRot = 0.0f;
        }
		//rotateZ = !rotateZ;
    }

	/* Rotate. */
    glRotatef( xRot, 1.0f, 0.0f, 0.0f );
	glRotatef( yRot, 0.0f, 1.0f, 0.0f );
	glRotatef( zRot, 0.0f, 0.0f, 1.0f ); /* Rotate. */

	//printCube( cube0, index );
	printParticle(particles, isovalue);

	glutSwapBuffers();
	glutPostRedisplay();
}

static
void keydown (unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':			/* delta, triangle */
		rotateX = !rotateX;
		break;
	case 'o':			/* round */
		rotateY = !rotateY;
		//delta = 0.0f;
		break;
	case 'q':			/* square*/
		rotateZ = !rotateZ;
		break;
	case 'x':			/* cross button */
		index += 1;
		break;
	case 's': // select	
		break;
	case 'a': //startbutton
		exit(1);
		//sceKernelExitGame();
		break;
	default:
		;
	}
}


static
void keyup (unsigned char key, int x, int y)
{
	switch (key) {
	case 'o':
		//delta = 1.0f;
		break;
	default:
		;
	}
}


static
void joystick (unsigned int buttonMask, int x, int y, int z)
{
	//glClearColor(x * 1.0f/2000.0f + 0.5f, y * 1.0f/2000.0f + 0.5f, 1.0f, 1.0f);
	deltaX = x * 1.0f/100.0f;
	deltaY = y * 1.0f/100.0f * -1.0f;
	//deltaZ = z * 1.0f/1000.0f + 0.5f;
}

int main(int argc, char *argv[]) {
	
	initCube(&cube0, 30.0f, 30.0f, 30.0f);
		
	setParticle(particles, 50.0f);

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // TODO: test on psp
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); // TODO: test on psp
	glutInitWindowPosition(0,0); // TODO: test on psp
	glutCreateWindow(__FILE__);
	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutJoystickFunc(joystick, 0);
	//glutReshapeFunc(reshape);
	//glutReshapeFunc(setupGL);
	glutDisplayFunc(display2);

	setupGL(SCREEN_WIDTH, SCREEN_HEIGHT);

	glutMainLoop();

	return 0;
}
