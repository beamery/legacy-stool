#include "Floor.h"

Floor::Floor() {

	// Initialize grid to a 10ft square, with points every 6 inches
	double xPos = 0;
	for (int i = 0; i < GRID_SIZE; i++) {
		double zPos = 0;
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

	// Draw axes
	// y coord offset by 0.01 to stop the lines from fighting each other
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	// x
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex4f(60.0f, 0.01f, 60.0f, 1.0f);
	glVertex4f(120.0f, 0.01f, 60.0f, 1.0f);
	// y
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex4f(60.0f, 0.0f, 60.0f, 1.0f);
	glVertex4f(60.0f, 60.0f, 60.0f, 1.0f);
	// z
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex4f(60.0f, 0.01f, 60.0f, 1.0f);
	glVertex4f(60.0f, 0.01f, 120.0f, 1.0f);
	glEnd();


	// Draw floor grid
	glLineWidth(1.0f);
	for (int i = 0; i < GRID_SIZE - 1; i++) {
		glBegin(GL_LINE_LOOP);
		glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
		for (int j = 0; j < GRID_SIZE - 1; j++) {
			glVertex4f(grid[i][j].x, 0.0f, grid[i][j].z, 1.0f);
			glVertex4f(grid[i+1][j].x, 0.0f, grid[i+1][j].z, 1.0f);
			glVertex4f(grid[i+1][j+1].x, 0.0f, grid[i+1][j+1].z, 1.0f);
			glVertex4f(grid[i][j+1].x, 0.0f, grid[i][j+1].z, 1.0f);
		}
		glEnd();
	}
	// restore previous modelview matrix
	mViewStack.pop();
}
