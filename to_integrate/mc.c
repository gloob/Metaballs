/*
 * Marching Cubes PRACTIK!
 *
 * <GlooB / TsT>
 *
 */

#include <windows.h>

#include "SDL.h"

#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>

#include "cubeDef.h"

static GLboolean rotateX = GL_FALSE;
static GLboolean rotateY = GL_FALSE;
static GLboolean rotateZ = GL_FALSE;

static GLfloat deltaX = 0.0f;
static GLfloat deltaY = 0.0f;
static GLfloat deltaZ = -50.0f;

#define DIV_X 10
#define DIV_Y 10
#define DIV_Z 10

static GLfloat stepX = 5.0f;
static GLfloat stepY = 5.0f;
static GLfloat stepZ = 5.0f;

static GLfloat isovalor = 50.0f;

#define NUM_PARTICLES 1


typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLboolean sel;
} vertex;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLclampf r;
	GLclampf g;
	GLclampf b;
	vertex vertexs[DIV_X*DIV_Y*DIV_Z];
} particle;

particle particles[NUM_PARTICLES];

int setParticle( particle *ptr )
{
	int p, i, j, k;
	GLfloat initX, initY, initZ;
	GLfloat incX, incY, incZ;
	GLfloat total;
	double media = 0.0f;

	int offset2 = DIV_Y*DIV_X;

	if( ptr == NULL ) {
		fprintf(stderr, "** El puntero ptr apunta a NULL!");
		return -1;
	}

	
	for(p = 0; p < NUM_PARTICLES; p++)
	{
		
		particles[p].x = p * 5.0f;
		particles[p].y = p * 5.0f;
		particles[p].z = p * 5.0f;
		particles[p].r = 1.0f;
		particles[p].g = 0.0f;
		particles[p].b = 0.5f;
		
		incX = initX = particles[p].x - (( stepX * DIV_X ) / 2) + (stepX / 2);
		incY = initY = particles[p].y - (( stepY * DIV_Y ) / 2) + (stepY / 2);
		incZ = initZ = particles[p].z - (( stepZ * DIV_Z ) / 2) + (stepZ / 2);	
		
		printf("* InitX = %f\n", initX);
		printf("* InitY = %f\n", initY);
		printf("* InitZ = %f\n", initZ);

		for(k = 0; k < DIV_Z; k++) {
			incY = initY;
			for(j = 0; j < DIV_Y; j++) {
				incZ = initZ;
				for(i = 0; i < DIV_X; i++) {
					particles[p].vertexs[(j*DIV_X)+(k*offset2)+i].x = incX;
					particles[p].vertexs[(j*DIV_X)+(k*offset2)+i].y = incY;
					particles[p].vertexs[(j*DIV_X)+(k*offset2)+i].z = incZ;
					//printf("[%d][%d][%d] (%d) X = %f Y = %f Z = %f\n", i, j, k, (j*DIV_X)+(k*DIV_Y*DIV_X)+i, incX, incY, incZ);
					
					total = (particles[p].x - incX) * (particles[p].x - incX) +
							(particles[p].y - incY) * (particles[p].y - incY) +
							(particles[p].z - incZ) * (particles[p].z - incZ);
					//printf("[%d][%d][%d] = %f\n", i, j, k, total);
					media += total;
					if( total <= isovalor )
						particles[p].vertexs[(j*DIV_X)+(k*offset2)+i].sel = GL_TRUE;
					else 
						particles[p].vertexs[(j*DIV_X)+(k*offset2)+i].sel = GL_FALSE;

					incZ += stepZ;
				}
				incY += stepY;	
			}
			incX += stepX;
		}	
	}

	media = media / (DIV_X*DIV_Y*DIV_Z);
	printf("media = %f", media);
	isovalor = (float) media / 1.75;
	return 1;
}

void isoParticle(float isovalue)
{
	int tope = DIV_X * DIV_Y * DIV_Z;
	int i, p;
	float total;
	static float oldisovalue;
	
	if(oldisovalue != isovalue) {
		oldisovalue = isovalue;
		for(p = 0; p < NUM_PARTICLES; p++)
		{
			for(i=0; i<tope; i++) {
				total = (particles[p].x - particles[p].vertexs[i].x) * 
					    (particles[p].x - particles[p].vertexs[i].x) +
						(particles[p].y - particles[p].vertexs[i].y) * 
						(particles[p].y - particles[p].vertexs[i].y) +
						(particles[p].z - particles[p].vertexs[i].z) * 
						(particles[p].z - particles[p].vertexs[i].z);
						//printf("[%d] = %f; %f; %f; Dist = %f\n", i, particles[p].vertexs[i].x, 
						//	    particles[p].vertexs[i].y, particles[p].vertexs[i].z, total);
				if( total <= isovalue )
					particles[p].vertexs[i].sel = GL_TRUE;
				else 
					particles[p].vertexs[i].sel = GL_FALSE;
			}
		}
	}
}

void printParticle( void )
{
	int p, i, j, k;

	isoParticle(isovalor);

	glBegin( GL_POINTS );
	
	for(p = 0; p < NUM_PARTICLES; p++)
	{
		glColor3f(particles[p].r, particles[p].g, particles[p].b);
		glVertex3f(particles[p].x, particles[p].y, particles[p].z);
		
		//glColor3f( 0.5f, 0.5f, 0.5f );
		for(i = 0; i < DIV_X * DIV_Y * DIV_Z; i++) {
			if(particles[p].vertexs[i].sel) 
				glColor3f( 1.0f, 0.0f, 1.0f );
			else
				glColor3f( 0.0f, 1.0f, 1.0f );

			glVertex3f(	particles[p].vertexs[i].x,
						particles[p].vertexs[i].y,
						particles[p].vertexs[i].z);
		}
	}

	glEnd();
}

void exitSDL(int err_code)
{
	SDL_Quit();
	
	exit(err_code);
}

SDL_Surface *startSDL( int w, int h )
{
	const SDL_VideoInfo *info = NULL;
	SDL_Surface *screen;
	
	Uint8 bpp;
	Uint32 flags;
	int rgb_size[3];
	int value;

	// Inicializar SDL
	printf("· Initializing SDL...");
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("[FAIL!]\n");
		fprintf(stderr, "* ERROR: Can´t initialize SDL system. [%s]\n", SDL_GetError());
		exitSDL(-1);
	}
	printf("[OK!]\n");

	// Request video info...yeahh!
	info = SDL_GetVideoInfo();

	printf("· Video Query...");
	if(!info) {
		printf("[FAIL!]\n");
		fprintf(stderr, "* ERROR: Video query fail. [%s]\n", SDL_GetError());
		exitSDL(-1);
	}
	printf("[OK!]\n");

	bpp = info->vfmt->BitsPerPixel;

	switch (bpp)
	{
	    case 8:
			rgb_size[0] = 2;
			rgb_size[1] = 3;
			rgb_size[2] = 3;
			break;
	    case 15:
	    case 16:
			rgb_size[0] = 5;
			rgb_size[1] = 5;
			rgb_size[2] = 5;
			break;
        default:
			rgb_size[0] = 8;
			rgb_size[1] = 8;
			rgb_size[2] = 8;
			break;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rgb_size[0]);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, rgb_size[1]);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rgb_size[2]);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//  SDL_GL_SetAttributes(SDL_GL_STENCIL_SIZE, 8);

	flags = SDL_OPENGL | SDL_FULLSCREEN;
	flags = 0;
	flags = SDL_OPENGL;

	/* Set the video mode */
	printf("· Video Mode Set...");
	
	screen = SDL_SetVideoMode( w, h, bpp, flags);
	if(screen == NULL) {
		printf("[FAIL!]\n");
		fprintf(stderr, "* ERROR: Video set fail. [%s]\n", SDL_GetError());
		exitSDL(-1);
	} 
	printf("[OK!]\n");

	printf("\n");
	printf( "\t##  Vendor     : %s\n", glGetString( GL_VENDOR ) );
	printf( "\t##  Renderer   : %s\n", glGetString( GL_RENDERER ) );
	printf( "\t##  Version    : %s\n", glGetString( GL_VERSION ) );
	printf( "\t##  Extensions : %s\n", glGetString( GL_EXTENSIONS ) );
	printf("\n");

	SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &value );
	printf( "\t##  SDL_GL_RED_SIZE: requested %d, got %d\n", rgb_size[0],value);
	SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &value );
	printf( "\t##  SDL_GL_GREEN_SIZE: requested %d, got %d\n", rgb_size[1],value);
	SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &value );
	printf( "\t## SDL_GL_BLUE_SIZE: requested %d, got %d\n", rgb_size[2],value);
	SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &value );
	printf( "\t## SDL_GL_DEPTH_SIZE: requested %d, got %d\n", bpp, value );
	SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &value );
	printf( "\t## SDL_GL_DOUBLEBUFFER: requested 1, got %d\n", value );
	SDL_GL_GetAttribute( SDL_GL_STENCIL_SIZE, &value );
	printf( "\t## SDL_GL_STENCIL_SIZE: requested 8, got %d\n", value );
	
	return screen;
}

static void setupGL( GLsizei w, GLsizei h)
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
	glClearColor( 0.0f, 0.0f, 0.5f, 1.0f);
	glClearDepth( 1.0f );

	// Desactivar test de profundidad.
	glDisable( GL_DEPTH_TEST );

	// Activar el Blending.
//	glEnable( GL_BLEND );
//	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	// Color de pincel.
	glColor3f( 1.0f, 0.0f, 0.0f );

		// PIXELS DEFINITIONS!!
	//Definir tamaño del punto.
	glPointSize( 3.0f );
    // Activar "antialiasing" de puntos
//	glEnable( GL_POINT_SMOOTH );


}

// Manejador de evento "tecla abajo"
static void handle_key_down( SDL_keysym *keysym )
{
	switch( keysym->sym ) {
	case SDLK_1:
		rotateX = !rotateX;
		break;

	case SDLK_2:
		rotateY = !rotateY;
		break;

	case SDLK_3:
		rotateZ = !rotateZ;
		break;

	case SDLK_4:
		isovalor += 10.0f;
		break;

	case SDLK_5:
		isovalor -= 10.0f;
		break;

	case SDLK_RIGHT:
		deltaX += 1.0f;
		break;

	case SDLK_LEFT:
		deltaX -= 1.0f;
		break;

	case SDLK_UP:
		deltaY += 1.0f;
		break;

	case SDLK_DOWN:
		deltaY -= 1.0f;
		break;

	case SDLK_q:
		deltaZ -= 1.0f;
		break;

	case SDLK_a:
		deltaZ += 1.0f;
		break;

	case SDLK_ESCAPE:
		exitSDL(1);
		break;

	case SDLK_SPACE:
		break;
		
	default:
		break;
	}
}

// Cola de eventos...
static void procEvents( void )
{
	SDL_Event event;

	while( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
			case SDL_KEYDOWN:
				handle_key_down( &event.key.keysym );
				break;

			case SDL_KEYUP:
				break;

			case SDL_QUIT:
				exitSDL(1);
				break;

			default:
				break;
		}
	}
}

static void drawGL( void )
{
	static GLfloat xRot = 0.0f, yRot = 0.0f, zRot = 0.0f;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/* We don't want to modify the projection matrix. */
 //   glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    /* Move down the z-axis. */
    glTranslatef( deltaX, deltaY, deltaZ );

    /* Rotate. */
    glRotatef( xRot, 1.0f, 0.0f, 0.0f );
	glRotatef( yRot, 0.0f, 1.0f, 0.0f );
	glRotatef( zRot, 0.0f, 0.0f, 1.0f );

    if( rotateX ) {
        if( ++xRot > 360.0f ) {
            xRot = 0.0f;
        }
    }

    if( rotateY ) {
        if( ++yRot > 360.0f ) {
            yRot = 0.0f;
        }
    }

    if( rotateZ ) {
        if( ++zRot > 360.0f ) {
            zRot = 0.0f;
        }
    }


	// Draw the ground.
	printParticle();

	SDL_GL_SwapBuffers();
}

int main(int argc, char *argv[])
{

	SDL_Surface *screen;

	if( setParticle( particles ) == -1 )
		return -1;

	screen = startSDL( 640, 480 );
	
	setupGL( 640, 480 );

	while( 1 ) {
		procEvents();
		drawGL();
	}

	return 0;
}
