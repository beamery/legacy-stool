#ifndef VASE_H
#define VASE_H

#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Constants.h"

#define VASE_VSTEP_SIZE 2.0f
#define VASE_RSTEP_SIZE 0.1f * PI

/*
 * The Vase class draws what is basically a cylinder, augmented by 
 * a sine wave. This allows for some interesting and realistic 
 * looking curvatures, used to model various curved, vase-like
 * objects.
 */
class Vase {
public:

	/* Creates a vase.
	 *
	 * curveMag: adjusts the magnitude of the curvature
	 * curveFreq: adjusts the frequency of the curvature
	 * curveOffset: shifts the curvature up or down
	 * slices: number of horizontal slices
	 * stacks: number of vertical stacks
	 */
	Vase(glm::vec3 pos, 
		 float height,
		 float radius,
		 float curveMag, 
		 float curveFreq, 
		 float curveOffset,
		 int slices,
		 int stacks);

	void draw(MatrixStack &mViewStack);
	glm::vec3 getPos();

private:
	void drawBase(MatrixStack &mViewStack);
	float height, cMag, cFreq, cOffset, rad;
	int slices, stacks;
	glm::vec3 pos;
	float r, g, b;
};


#endif