#include "Stool.h"

Stool::Stool(float x, float z)  : 
	pos(glm::vec3(x, 0.0f, z)), heightAdjust(1.0f) {}

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
	
	// seat and stem rendering
	mViewStack.push();
	// used in height adjustment controls
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, heightAdjust, 0.0f));
	drawSeatAndStem(mViewStack);
	mViewStack.pop();

	// leg rendering
	drawLeg(mViewStack, 0);
	drawLeg(mViewStack, 90);
	drawLeg(mViewStack, 180);
	drawLeg(mViewStack, 270);

	mViewStack.pop();
}

void Stool::adjustHeight(float amount) {
	heightAdjust += amount;
	heightAdjust = max(0.0f, heightAdjust);
	heightAdjust = min(heightAdjust, 4.375f);
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
	gluCylinder(q, STEM_DIAM / 2, STEM_DIAM / 2, STEM_LENGTH, 10, 1); 
	mViewStack.pop();

	mViewStack.pop();

	gluDeleteQuadric(q);
}

/*
 * Draws one leg of the stool. The shear pushes the foot of the leg out 
 * in the positive x direction.
 * 
 * Note: the shear factor must have LEG_LENGTH / 2 added to its denominator
 * because the center of the leg is viewed as y = 0 at the time it is sheared.
 */
void Stool::drawLeg(MatrixStack &mViewStack, float rotation) {
	glm::mat4 shearMat;
	glm::vec4 shearVec(-SHEAR_DIST / (LEG_LENGTH), 1.0f, 0.0f, 0.0f);
	shearMat[1] = shearVec;

	mViewStack.push();

	// rotate the leg to position it on the stool
	mViewStack.active = glm::rotate(mViewStack.active, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	// get basic leg shape
	
	// stretch it, position it on the ground and shear it
	mViewStack.active = mViewStack.active * shearMat;
	mViewStack.active = glm::translate(mViewStack.active,  
		glm::vec3(LEG_HORIZ_OFFSET - SHEAR_DIST, -STOOL_HEIGHT + LEG_LENGTH / 2, 0.0f));
	mViewStack.active = glm::scale(mViewStack.active, 
		glm::vec3(LEG_THICKNESS, LEG_LENGTH, LEG_THICKNESS));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor4f(0.4f, 0.9f, 0.4f, 1.0f);
	glutSolidCube(1);

	mViewStack.pop();

	/*glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glBegin(GL_LINES);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(LEG_HORIZ_OFFSET, 1.0f, 0.0f);
	glVertex3f(LEG_HORIZ_OFFSET, -40.0f, 0.0f);
	glEnd();*/
}
