/*
 * 
 *
 * gloob / TsT
 *
 * $Id$							
 *
 */

#include <iostream>

#include "vertex.h"


Vertex::~Vertex() 
{
	
}

void Vertex::display() 
{
	printf("x: %f, y: %f, z: %f\n", this->x, this->y, this->z);
}