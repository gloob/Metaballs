/*
 * Particle definition
 *
 * Copyright (c) 2011 Alejandro Leiva <gloob@litio.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Author: Alejandro Leiva <gloob@litio.org>
 *
 */

#include "cube.h"

#define DIV 5
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
