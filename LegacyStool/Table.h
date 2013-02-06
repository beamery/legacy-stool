#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"

// measurements in inches
#define TABLE_HEIGHT 37.325f
#define TABLE_WIDTH 43.25f
#define TABLE_LENGTH 43.25f
#define TABLE_LEG_THICKNESS 2.5f
#define TABLE_TOP_THICKNESS 1.0f
#define TABLE_SIDE_THICKNESS 1.0f

// Contains position and rendering data for a table
class Table {

public:
	// initialize table with the given position and length
	Table(glm::vec3 position);

	// return table position as a glm::vec3
	glm::vec3 getPos() const;

	// render the stool
	void draw(MatrixStack &mViewStack);

private:
	void drawLeg(MatrixStack &mViewStack, float xOffset, float zOffset);
	void drawSide(
		MatrixStack &mViewStack, 
		float xOffset, float zOffset, float xScale, float zScale);
	glm::vec3 pos;
};


#endif