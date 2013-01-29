#include "Floor.h"

Floor::Floor() {

	// Initialize grid to a 10ft square, with points every 6 inches
	int xPos = 0;
	for (int i = 0; i < GRID_SIZE; i++) {
		int zPos = 0;
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = glm::vec3(xPos, 0, zPos);
			zPos += 6;
		}
		xPos += 6;
	}
}


void Floor::draw(MatrixStack &mViewStack) {
	// save previous modelview matrix
	mViewStack.push();

	for (int i = 0; i < GRID_SIZE - 1; i++) {
		glBegin(GL_QUAD_STRIP);
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		for (int j = 0; j < GRID_SIZE; j++) {
			glVertex4f(grid[i][j].x, -1.0f, grid[i][j].z, 1.0f);
			glVertex4f(grid[i+1][j].x, -1.0f, grid[i+1][j].z, 1.0f);
		}
		glEnd();
	}

	// restore previous modelview matrix
	mViewStack.pop();
}
