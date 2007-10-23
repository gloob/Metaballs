/*
 * 
 *
 * gloob / TsT
 *
 * $Id$							
 *
 */

#include "cube.h"

#define DIV 2
#define DIV_X DIV
#define DIV_Y DIV
#define DIV_Z DIV
#define NUM_CUBES (DIV_X-1)*(DIV_Y-1)*(DIV_Z-1)

//#define NUM_PARTICLES 10

static GLfloat stepX = 5.0f;
static GLfloat stepY = 5.0f;
static GLfloat stepZ = 5.0f;

//TODO: Refactor data structures.
//      vector(x,y,z,selected)
//		cube: pointer to six vectors in memory
//		particle: numcube pointers to cube structures.
		
typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLclampf r;
	GLclampf g;
	GLclampf b;
	vertex vertexs[DIV_X*DIV_Y*DIV_Z];
	cube cubes[NUM_CUBES];
} particle;

int setParticle(particle *p, float isovalue);
void printParticle(particle *p, float isovalue);
