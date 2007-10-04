/*
 * Header file for vector functions & structures.
 *
 * gloob / TsT
 *
 * $Id$							
 *
 */


typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLboolean sel;
} vertex;


void initCube(cube *, float, float, float);
void printCube(cube, unsigned char);

