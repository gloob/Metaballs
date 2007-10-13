/*
 * Header file for vector functions & structures.
 *
 * gloob / TsT
 *
 * $Id$							
 *
 */


class Vertex {
	
public:
	float x, y, z;
	int	sel;
	
	Vertex(): x(0.0f), y(0.0f), z(0.0f) {};
	Vertex(float vx, float vy, float vz): x(vx), y(vy), z(vz) {};
	~Vertex();
	void display();
};