/*
 * 
 *
 * gloob / TsT
 *
 * $Id$							
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include "gl.h"

#include "particle.h"

int setParticle( particle *particles, float isovalue )
{
	int p, i, j, k;
	GLfloat initX, initY, initZ;
	GLfloat incX, incY, incZ;
	GLfloat total;
	double media = 0.0f;

	int offset2 = DIV_Y*DIV_X;

	p = 0;
//	for(p = 0; p < NUM_PARTICLES; p++) {

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
					printf("[%d][%d][%d] (%d) X = %f Y = %f Z = %f\n", i, j, k, (j*DIV_X)+(k*DIV_Y*DIV_X)+i, incX, incY, incZ);

					total = (particles[p].x - incX) * (particles[p].x - incX) +
							(particles[p].y - incY) * (particles[p].y - incY) +
							(particles[p].z - incZ) * (particles[p].z - incZ);
					printf("[%d][%d][%d] = %f\n", i, j, k, total);
					media += total;
					if( total <= isovalue )
						particles[p].vertexs[(j*DIV_X)+(k*offset2)+i].sel = GL_TRUE;
					else 
						particles[p].vertexs[(j*DIV_X)+(k*offset2)+i].sel = GL_FALSE;

					incZ += stepZ;
				}
				incY += stepY;	
			}
			incX += stepX;
		}	
	//}

	media = media / (DIV_X*DIV_Y*DIV_Z);
	//printf("media = %f", media);
	isovalue = (float) media / 1.75;
	
	//start cubes
	int idx = 0;
	incX = initX = particles[p].x - (( stepX * DIV_X ) / 2) + (stepX / 2);
	incY = initY = particles[p].y - (( stepY * DIV_Y ) / 2) + (stepY / 2);
	incZ = initZ = particles[p].z - (( stepZ * DIV_Z ) / 2) + (stepZ / 2);

	printf("* InitX = %f\n", initX);
	printf("* InitY = %f\n", initY);
	printf("* InitZ = %f\n", initZ);
	printf("* stepX  = %f\n", stepX);


	for (k = 0; k < DIV_Z-1; k++) {
		incY = initY;
		for (j = 0; j < DIV_Y-1; j++) {
			incZ = initZ;
			for (i = 0; i < DIV_X-1; i++) {
				initCube(&particles[p].cubes[idx++], incX, incY, incZ);
				printf("x: %f, y: %f, z:%f\n", incX, incY, incZ);
				incZ += stepZ;
			}
			incY += stepY;
		}
		incX += stepX;
	}
	return 1;
}

void isoParticle(particle *particles, float isovalue)
{
	int tope = DIV_X * DIV_Y * DIV_Z;
	int i, p;
	float total;
	static float oldisovalue;
	
	int cindex = 0;

	if(oldisovalue != isovalue) {
		oldisovalue = isovalue;
		
		p = 0;
		//for(p = 0; p < NUM_PARTICLES; p++) {
			
			for(i=0; i<tope; i++) {
				
				/*
				if ((i % 3) == 0 && cindex < NUM_CUBES) {
					
					initCube(&particles[p].cubes[cindex], 
							particles[p].vertexs[i].x, 
							particles[p].vertexs[i].y, 
							particles[p].vertexs[i].z);
					cindex++;
				}
				*/
				
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
		//}
	}
	
}

void printParticle(particle *particles, float isovalue)
{
	int p, i, j, k;

	isoParticle(particles, isovalue);

	glBegin( GL_POINTS );

	p = 0;
	//for(p = 0; p < NUM_PARTICLES; p++)
	//{
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
	//}
	
		for (i = 0; i < NUM_CUBES; i++) {
			printCube(particles[p].cubes[i], particles[p].vertexs[i].sel);
		}

	glEnd();
}

