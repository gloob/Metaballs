/*
 * 
 *
 * GlooB / TsT
 *
 * v 0.1							
 *
 */

#include <GL/gl.h>
#include <GL/glut.h>

#include "cube.h"
#include "mcdef.h"

void initCube(cube* cube0)
{
	int i;

	for(i=0;i<NUM_CUBE_VERTEX;i++) {
		cube0->vertexs[i].sel = FALSE;
	}

	cube0->vertexs[0].x = -POS; cube0->vertexs[0].y = -POS; cube0->vertexs[0].z =  POS;
	cube0->vertexs[1].x =  POS; cube0->vertexs[1].y = -POS; cube0->vertexs[1].z =  POS;
	cube0->vertexs[2].x =  POS; cube0->vertexs[2].y = -POS; cube0->vertexs[2].z = -POS;
	cube0->vertexs[3].x = -POS; cube0->vertexs[3].y = -POS; cube0->vertexs[3].z = -POS;
	cube0->vertexs[4].x = -POS; cube0->vertexs[4].y =  POS; cube0->vertexs[4].z =  POS;
	cube0->vertexs[5].x =  POS; cube0->vertexs[5].y =  POS; cube0->vertexs[5].z =  POS;
	cube0->vertexs[6].x =  POS; cube0->vertexs[6].y =  POS; cube0->vertexs[6].z = -POS;
	cube0->vertexs[7].x = -POS; cube0->vertexs[7].y =  POS; cube0->vertexs[7].z = -POS;

	cube0->edges[0].a = &cube0->vertexs[0]; cube0->edges[0].b = &cube0->vertexs[1];
	cube0->edges[1].a = &cube0->vertexs[1]; cube0->edges[1].b = &cube0->vertexs[2];
	cube0->edges[2].a = &cube0->vertexs[2]; cube0->edges[2].b = &cube0->vertexs[3];
	cube0->edges[3].a = &cube0->vertexs[3]; cube0->edges[3].b = &cube0->vertexs[0];
	cube0->edges[4].a = &cube0->vertexs[4]; cube0->edges[4].b = &cube0->vertexs[5];
	cube0->edges[5].a = &cube0->vertexs[5]; cube0->edges[5].b = &cube0->vertexs[6];
	cube0->edges[6].a = &cube0->vertexs[6]; cube0->edges[6].b = &cube0->vertexs[7];
	cube0->edges[7].a = &cube0->vertexs[7]; cube0->edges[7].b = &cube0->vertexs[4];
	cube0->edges[8].a = &cube0->vertexs[0]; cube0->edges[8].b = &cube0->vertexs[4];
	cube0->edges[9].a = &cube0->vertexs[1]; cube0->edges[9].b = &cube0->vertexs[5];
	cube0->edges[10].a = &cube0->vertexs[2]; cube0->edges[10].b = &cube0->vertexs[6];
	cube0->edges[11].a = &cube0->vertexs[3]; cube0->edges[11].b = &cube0->vertexs[7];

}

void printCube(cube cube0, unsigned char index)
{
	int i, j, k, e;


	//glPointSize( 1.0f );
	//glDisable( GL_POINT_SMOOTH );
	
	
	glBegin( GL_LINES );

	for(i=0;i<12;i++) {
		if( cube0.edges[i].a->sel || cube0.edges[i].b->sel ) {
			glColor3f( 0.0f, 1.0f, 0.0f );
			if(cube0.edges[i].a->sel) {
			   glColor3f( 1.0f, 0.0f, 0.0f );
			}
			glVertex3f( cube0.edges[i].a->x, cube0.edges[i].a->y, cube0.edges[i].a->z );
			
			glColor3f( 0.0f, 1.0f, 0.0f );
			if(cube0.edges[i].b->sel)
			   glColor3f( 1.0f, 0.0f, 0.0f );
			glVertex3f( cube0.edges[i].b->x, cube0.edges[i].b->y, cube0.edges[i].b->z );
		}
		else {
			glColor3f( 0.0f, 1.0f, 0.0f );
			glVertex3f( cube0.edges[i].a->x, cube0.edges[i].a->y, cube0.edges[i].a->z );
			glVertex3f( cube0.edges[i].b->x, cube0.edges[i].b->y, cube0.edges[i].b->z );
		}
	}

	glEnd();

	//glPointSize( 10.0f );
	//glEnable( GL_POINT_SMOOTH );

	glBegin( GL_POINTS );
	glColor3f( 1.0f, 0.0f, 0.0f );

	for(i = 0; i < NUM_CUBE_VERTEX; i++) {
		if( cube0.vertexs[i].sel )
			glColor3f( 1.0f, 0.0f, 0.0f );
		else
			glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( cube0.vertexs[i].x, cube0.vertexs[i].y, cube0.vertexs[i].z );
	}

	glEnd();

	glBegin( GL_TRIANGLES );
	//glColor4f( 1.0f, 0.0f, 0.0f, 0.5f );
	glColor3f( 0.5f, 0.0f, 0.0f );

	
	for( e = 0; e < 4; e++ )
	{
		i = cube_table[index][(e*3)];
		j = cube_table[index][(e*3)+1];
		k = cube_table[index][(e*3)+2];

		if( (i > -1) && (j > -1) && (k > -1) ) {
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex3f( (cube0.edges[i].a->x + cube0.edges[i].b->x) / 2,
					(cube0.edges[i].a->y + cube0.edges[i].b->y) / 2,
					(cube0.edges[i].a->z + cube0.edges[i].b->z) / 2 );
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( (cube0.edges[j].a->x + cube0.edges[j].b->x) / 2,
					(cube0.edges[j].a->y + cube0.edges[j].b->y) / 2,
					(cube0.edges[j].a->z + cube0.edges[j].b->z) / 2 );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex3f( (cube0.edges[k].a->x + cube0.edges[k].b->x) / 2,
					(cube0.edges[k].a->y + cube0.edges[k].b->y) / 2,
					(cube0.edges[k].a->z + cube0.edges[k].b->z) / 2 );
		}
	}

	glEnd();
}
