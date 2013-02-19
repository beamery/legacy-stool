#include "Vase.h"


Vase::Vase(glm::vec3 pos, float height, float radius, float curveMag, float curveFreq, 
		   float curveOffset, int slices, int stacks) : 
			pos(pos), height(height), rad(radius), cMag(curveMag), 
			cFreq(curveFreq), cOffset(curveOffset), slices(slices), stacks(stacks) {
			
				r = (rand() / float(RAND_MAX) * 0.5f) + 0.5f;
				g = (rand() / float(RAND_MAX) * 0.5f) + 0.5f;
				b = (rand() / float(RAND_MAX) * 0.5f) + 0.5f;
			}


void Vase::draw(MatrixStack &mViewStack) {

	mViewStack.push();

	// draw vase cylinder (skewed by sine)
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor3f(r, g, b);
	for (float y = 0; y < height; y += height / stacks) {
		glBegin(GL_QUAD_STRIP);
		for (float theta = 0; theta <= 2 * PI; theta +=  2 * PI / slices) {
			glVertex3f(
				(rad + cMag * sin((y + cOffset) * cFreq)) * sin(theta), 
				y, 
				(rad + cMag * sin((y + cOffset) * cFreq)) * cos(theta));
			glVertex3f(
				(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * sin(theta), 
				y + height / stacks, 
				(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * cos(theta));
		}
		// two more vertices at beginning for continuity
		glVertex3f(
			(rad + cMag * sin((y + cOffset) * cFreq)) * sin(0.0f), 
			y, 
			(rad + cMag * sin((y + cOffset) * cFreq)) * cos(0.0f));
		glVertex3f(
			(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * sin(0.0f), 
			y + height / stacks, 
			(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * cos(0.0f));
		glEnd();
	}

	GLUquadric *q = gluNewQuadric();

	// draw bottom of vase
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.01f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor3f(0.2f + r, 0.2f + g, 0.2f + b);
	gluDisk(q, 0.0f, rad - 0.0075f, 32, 1); // subtract small amount to prevent protrusion

	gluDeleteQuadric(q);
	mViewStack.pop();
}


glm::vec3 Vase::getPos() {
	return pos;
}