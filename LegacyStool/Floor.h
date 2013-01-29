#ifndef FLOOR_H
#define FLOOR_H

#define GRID_SIZE 20

#include <gl/freeglut.h>
#include "MatrixStack.h"

// Contains coordinates and drawing functionality for the floor of
// our world
class Floor {

public:
	Floor();
	void draw(MatrixStack &mViewStack);
private:
	glm::vec3 grid[GRID_SIZE][GRID_SIZE];

};


#endif