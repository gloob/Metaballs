/*
 * Cube definition
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


//void initCube(cube *, float, float, float);
void initCube(cube *, float, float, float, float);
void printCube(cube, unsigned char);

