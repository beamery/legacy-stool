#ifndef FLOOR_H
#define FLOOR_H

#define GRID_SIZE 21

#include <gl/freeglut.h>
#include "MatrixStack.h"

// Contains coordinates and drawing functionality for the floor of
// our world
class Floor {

public:

	// initializes the floor as a 10ft by 10ft grid, separated into
	// 6in by 6in sections
	Floor();

	// Draws the grid
	void draw(MatrixStack &mViewStack);

private:
	glm::vec3 grid[GRID_SIZE][GRID_SIZE];

};


#endif