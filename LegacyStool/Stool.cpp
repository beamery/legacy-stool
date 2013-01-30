#include "Stool.h"

Stool::Stool(float x, float z)  : 
	pos(glm::vec3(x, 0.0f, z)), heightAdjust(0.0f) {}

glm::vec3 Stool::getPos() const {
	return pos;
}

/* 
 * Draw the stool
 * Stool's base height is 0 (on the floor)
 * Dimensions:
 *  Seat diameter: 11 3/4 "
 *  Width: 14 5/8 "
 *  Depth: 19 5/8 "
 *  Min. seat height: 24 3/4 "
 *  Max. seat height: 29 1/8 "
 */
void Stool::draw(MatrixStack &mViewStack) {
	mViewStack.push();
	
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, STOOL_HEIGHT, 0.0f));
	
	mViewStack.push();
	// used in height adjustment controls
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, heightAdjust, 0.0f));
	drawSeatAndStem(mViewStack);
	mViewStack.pop();

	mViewStack.pop();
}

void Stool::print() const {
	cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")";
}

void Stool::drawSeatAndStem(MatrixStack &mViewStack) {
	mViewStack.push();
	// puts top of stool seat at height 0
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	GLUquadric *q = gluNewQuadric();
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	// divide by 2 to get radius
	gluCylinder(q, SEAT_DIAM / 2, SEAT_DIAM / 2, SEAT_THICKNESS, 32, 4); 
	mViewStack.pop();

	// draw top of stool seat
	// no translation needed since top is at height 0
	mViewStack.push();
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	gluDisk(q, 0, SEAT_DIAM / 2, 32, 4); // divide by 2 to get radius
	mViewStack.pop();

	// draw bottom of stool seat
	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -SEAT_THICKNESS, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
	gluDisk(q, 0, SEAT_DIAM / 2, 32, 1); // divide by 2 to get radius
	mViewStack.pop();

	// draw seat stem
	mViewStack.push();
	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -SEAT_THICKNESS, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
	gluCylinder(q, STEM_DIAM / 2, STEM_DIAM / 2, STEM_LENGTH, 32, 1); 
	mViewStack.pop();


	mViewStack.pop();

	gluDeleteQuadric(q);

}
