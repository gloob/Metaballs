/*
 * 
 *
 * gloob / TsT
 *
 * $Id$							
 *
 */

#include "cube.h"

#define DIV_X 10
#define DIV_Y 10
#define DIV_Z 10

//#define NUM_PARTICLES 10

static GLfloat stepX = 5.0f;
static GLfloat stepY = 5.0f;
static GLfloat stepZ = 5.0f;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLclampf r;
	GLclampf g;
	GLclampf b;
	vertex vertexs[DIV_X*DIV_Y*DIV_Z];
} particle;

