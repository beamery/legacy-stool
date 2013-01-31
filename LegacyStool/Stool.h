#ifndef STOOL_H
#define STOOL_H

// All measurements in inches
#define STOOL_HEIGHT 24.75f
#define SEAT_THICKNESS 0.7f
#define SEAT_DIAM 11.75f
#define STEM_LENGTH 12.0f
#define STEM_DIAM 1.05f

#define LEG_LENGTH 23.75f
#define LEG_THICKNESS 1.25f
#define LEG_HORIZ_OFFSET 8.8125f
#define SHEAR_DIST 5.98f

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
	Stool(float x = 0.0f, float z = 0.0f);

	// return stool position as a glm::vec3
	glm::vec3 getPos() const;

	// render the stool
	void draw(MatrixStack &mViewStack);

	// adjust the seat height
	void adjustHeight(float amount);

	// print the position of the stool
	void print() const;

private:
	void drawSeatAndStem(MatrixStack &mViewStack);
	void drawLeg(MatrixStack &mViewStack, float rotation);
	glm::vec3 pos;
	float heightAdjust;
};


#endif