#ifndef STOOL_H
#define STOOL_H

#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Constants.h"
#include "Utils.h"

// All measurements in inches
#define STOOL_HEIGHT 24.75f

#define SEAT_THICKNESS 0.5f
#define SEAT_DIAM 11.75f
#define STEM_LENGTH 10.5f
#define STEM_DIAM 1.05f

#define LEG_LENGTH 23.75f
#define LEG_THICKNESS 1.25f
#define LEG_HORIZ_OFFSET 8.8125f
#define SHEAR_DIST 5.98f

#define RING_OUTER_RAD 6.40f
#define RING_THICKNESS 0.35f
#define RING_HEIGHT 7.0f

#define TOP_DISK_RAD 2.8f
#define BOT_DISK_RAD 3.3f
#define DISK_THICKNESS 0.8f


// Contains position as well as rendering information for a single stool
class Stool	{

public:
	// initialize stool with the given position
	Stool(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

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
	void drawRing(MatrixStack &mViewStack);
	void drawDisk(MatrixStack &mViewStack, float radius, float height);
	glm::vec3 pos;
	float heightAdjust;

	// this function moved to Utils.h
	//void drawSkewedDisk(MatrixStack &mViewStack, float inRad, float outRad, 
		//float height, int slices);
};


#endif