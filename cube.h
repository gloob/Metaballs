/*
 * Header file for cube functions & structures.
 *
 * gloob / TsT
 *
 * $Id$							
 *
 */

/*  Constants definitions for cube. 
 */
#define NUM_CUBE_PERMS		256
#define NUM_CUBE_VERTEX		8
#define NUM_CUBE_EDGES		12
#define NUM_CUBE_SAMPLES	15
#define NUM_CUBE_ROTS		24

#define TRUE 1
#define FALSE 0

#define POS 10

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLboolean sel;
} vertex;

typedef struct {
	vertex* a;
	vertex* b;
} edge;

typedef struct {
	vertex vertexs[NUM_CUBE_VERTEX];
	edge edges[NUM_CUBE_EDGES];
} cube;


void initCube(cube *, float, float, float);
void printCube(cube, unsigned char);

