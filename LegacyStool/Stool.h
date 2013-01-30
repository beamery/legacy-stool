#ifndef STOOL_H
#define STOOL_H

// All measurements in inches
#define STOOL_HEIGHT 13.0f
#define SEAT_THICKNESS 1.0f
#define SEAT_DIAM 11.75f
#define STEM_LENGTH 12.0f
#define STEM_DIAM 1.0f

#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"

// Contains position as well as rendering information for a single stool
class Stool	{

public:
	// initialize stool with the given position
	Stool(float x = 0, float z = 0);

	// return stool position as a glm::vec3
	glm::vec3 getPos() const;

	// render the stool
	void draw(MatrixStack &mViewStack);

	// print the position of the stool
	void print() const;

private:
	void drawSeatAndStem(MatrixStack &mViewStack);
	glm::vec3 pos;
	float heightAdjust;
};


#endif