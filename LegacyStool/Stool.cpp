#include "Stool.h"

Stool::Stool(glm::vec3 position)  : 
	pos(position), heightAdjust(0.2f) {}

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
	
	// position stool with feet on the floor
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

	// draw lower ring
	drawRing(mViewStack);

	// draw upper disks
	drawDisk(mViewStack, TOP_DISK_RAD, 23.75f);
	drawDisk(mViewStack, BOT_DISK_RAD, 21.25f);

	mViewStack.pop();
}

void Stool::adjustHeight(float amount) {
	heightAdjust += amount;
	heightAdjust = max(0.2f, heightAdjust);
	heightAdjust = min(heightAdjust, 4.575f);
}


void Stool::print() const {
	cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")";
}


/* 
 * Draws the seat and seat stem. These have adjustable height, changed with
 * the J and K keys.
 */
void Stool::drawSeatAndStem(MatrixStack &mViewStack) {
	mViewStack.push();
	// puts top of stool seat at height 0
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	GLUquadric *q = gluNewQuadric();
	glColor4f(0.2f, 0.7f, 0.7f, 1.0f);
	// divide by 2 to get radius
	gluCylinder(q, SEAT_DIAM / 2, SEAT_DIAM / 2, SEAT_THICKNESS, 32, 1); 
	mViewStack.pop();

	// draw top of stool seat
	// no translation needed since top is at height 0
	mViewStack.push();
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.3f, 0.8f, 0.8f, 1.0f);
	gluDisk(q, 0, SEAT_DIAM / 2, 32, 1); // divide by 2 to get radius
	mViewStack.pop();

	// draw bottom of stool seat
	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -SEAT_THICKNESS, 0.0f));
	mViewStack.push();
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.1f, 0.4f, 0.4f, 1.0f);
	gluDisk(q, 0, SEAT_DIAM / 2, 32, 1); // divide by 2 to get radius

	mViewStack.pop();

	// draw skewed disk at bottom of seat
	glColor4f(0.1f, 0.4f, 0.4f, 1.0f);
	drawSkewedDisk(mViewStack, SEAT_DIAM / 2 - 2.5f, SEAT_DIAM / 2, 0.5f, 32);

	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -0.5f, 0.0f));

	mViewStack.push();
	// bottom disk below skewed disk
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor4f(0.05f, 0.3f, 0.4f, 1.0f);
	gluDisk(q, 0, SEAT_DIAM / 2 - 2.5f, 32, 1);
	mViewStack.pop();

	// little skewed disk
	glColor4f(0.1f, 0.4f, 0.4f, 1.0f);
	drawSkewedDisk(mViewStack, STEM_DIAM / 2, STEM_DIAM / 2 + 1, 0.2f, 32);

	mViewStack.pop();

	mViewStack.pop();

	// draw seat stem
	mViewStack.push();

	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -SEAT_THICKNESS, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.2f, 0.7f, 0.7f, 1.0f);
	gluCylinder(q, STEM_DIAM / 2, STEM_DIAM / 2, STEM_LENGTH, 10, 1); 
	mViewStack.pop();

	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, 
		glm::vec3(0.0f, -SEAT_THICKNESS - STEM_LENGTH, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.1f, 0.4f, 0.4f, 1.0f);
	gluDisk(q, 0.0, STEM_DIAM / 2, 32, 1); 
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
	
	// stretch it, position it on the ground and shear it
	mViewStack.active = mViewStack.active * shearMat;
	mViewStack.active = glm::translate(mViewStack.active,  
		glm::vec3(LEG_HORIZ_OFFSET - SHEAR_DIST, -STOOL_HEIGHT + LEG_LENGTH / 2, 0.0f));
	mViewStack.active = glm::scale(mViewStack.active, 
		glm::vec3(LEG_THICKNESS, LEG_LENGTH, LEG_THICKNESS));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor4f(0.4f, 0.8f, 0.4f, 1.0f);
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

/*
 * Draws the ring in the lower portion of the stool.
 *
 * Note: Inner radius of the ring actually specifies the thickness of the ring.
 * Outer radius specifies the radius of the ring itself
 */
void Stool::drawRing(MatrixStack &mViewStack) {
	mViewStack.push();

	// perform transformations on the torus
	mViewStack.active = glm::translate(mViewStack.active, 
		glm::vec3(0.0f, -(STOOL_HEIGHT - RING_HEIGHT), 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	GLUquadric *q = gluNewQuadric();
	glColor4f(0.7f, 0.7f, 1.0f, 1.0f);
	glutSolidTorus(RING_THICKNESS, RING_OUTER_RAD, 10, 20);

	gluDeleteQuadric(q);
	mViewStack.pop();
}

/*
 * Draws the two disk-like objects near the top of the stool.
 * This process is very similar to drawing the seat.
 */
void Stool::drawDisk(MatrixStack &mViewStack, float radius, float height) {
	mViewStack.push();

	// position disk vertically
	mViewStack.active = glm::translate(mViewStack.active, 
		glm::vec3(0.0f, - STOOL_HEIGHT + height, 0.0f));

	mViewStack.push();
	
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	// draw cylinder composing the sides of the disk
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	GLUquadric *q = gluNewQuadric();
	glColor4f(0.6f, 0.6f, 1.0f, 1.0f);
	gluCylinder(q, radius, radius, DISK_THICKNESS, 32, 1); 
	mViewStack.pop();

	// draw top of disk
	// no translation needed since top is at height 0
	mViewStack.push();
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.7f, 0.7f, 1.0f, 1.0f);
	gluDisk(q, STEM_DIAM / 2, radius, 32, 1); // divide by 2 to get radius
	mViewStack.pop();

	// draw bottom of disk
	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -DISK_THICKNESS, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	glColor4f(0.3f, 0.3f, 1.0f, 1.0f);
	gluDisk(q, STEM_DIAM / 2, radius, 32, 1); // divide by 2 to get radius
	gluDeleteQuadric(q);
	mViewStack.pop();
	mViewStack.pop();
}

/* MOVED to Utils.cpp
void Stool::drawSkewedDisk(MatrixStack &mViewStack, float inRad, float outRad, 
						   float height, int slices) {
	mViewStack.push();

	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor4f(0.1f, 0.4f, 0.4f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	for (float theta = 0; theta <= 2 * PI; theta +=  2 * PI / slices) {
		glVertex3f(inRad * cos(theta), -height, inRad * sin(theta));
		glVertex3f(outRad * cos(theta), 0.0f, outRad * sin(theta));
	}
	// two more vertices at beginning for continuity
		glVertex3f(inRad * cos(0.0f), -height, inRad * sin(0.0f));
		glVertex3f(outRad * cos(0.0f), 0.0f, outRad * sin(0.0f));
	glEnd();
	mViewStack.pop();
}*/

