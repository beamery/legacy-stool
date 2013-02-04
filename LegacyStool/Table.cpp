#include "Table.h"

Table::Table(glm::vec3 position) : pos(position) {}

glm::vec3 Table::getPos() const {
	return pos;
}

void Table::draw(MatrixStack &mViewStack) {
	mViewStack.push();

	// position table with feet on the floor
	mViewStack.active = glm::translate(
		mViewStack.active, 
		glm::vec3(0.0f, TABLE_HEIGHT - TABLE_TOP_THICKNESS / 2, 0.0f));

	// draw table top
	mViewStack.push();
	mViewStack.active = glm::scale(
		mViewStack.active, glm::vec3(
		TABLE_WIDTH, TABLE_TOP_THICKNESS, TABLE_LENGTH));
	glColor3f(0.0f, 0.5f, 0.5f);
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glutSolidCube(1.0);
	mViewStack.pop();

	// draw legs
	drawLeg(mViewStack, 
		(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);
	drawLeg(mViewStack, 
		(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		-(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);
	drawLeg(mViewStack, 
		-(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);
	drawLeg(mViewStack, 
		-(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		-(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);

	// draw table sides
	drawSide(mViewStack, 
		(TABLE_WIDTH - TABLE_SIDE_THICKNESS) / 2, 0.0f, 1.0f, 
		TABLE_WIDTH - 2 * TABLE_LEG_THICKNESS);
	drawSide(mViewStack, 
		-(TABLE_WIDTH - TABLE_SIDE_THICKNESS) / 2, 0.0f, 1.0f, 
		TABLE_WIDTH - 2 * TABLE_LEG_THICKNESS);
	drawSide(mViewStack, 
		0.0f, (TABLE_WIDTH - TABLE_SIDE_THICKNESS) / 2,
		TABLE_WIDTH - 2 * TABLE_LEG_THICKNESS, 1.0f);

	mViewStack.pop();
}

void Table::drawLeg(MatrixStack &mViewStack, float xOffset, float zOffset) {
	mViewStack.push();
	mViewStack.active = glm::translate(
		mViewStack.active, glm::vec3(
			xOffset, 
			-(TABLE_HEIGHT) / 2, 
			zOffset));

	mViewStack.active = glm::scale(mViewStack.active, glm::vec3(
		TABLE_LEG_THICKNESS,                  // x
		TABLE_HEIGHT - TABLE_TOP_THICKNESS,   // y
		TABLE_LEG_THICKNESS));                // z
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor3f(0.5f, 0.0f, 0.5f);
	glutSolidCube(1.0);
	mViewStack.pop();
}

void Table::drawSide(
	MatrixStack &mViewStack, 
	float xOffset, float zOffset, float xScale, float zScale) {

	mViewStack.push();
	mViewStack.active = glm::translate(
		mViewStack.active, 
		glm::vec3(
			xOffset, 
			-(TABLE_LEG_THICKNESS + TABLE_TOP_THICKNESS) / 2, 
			zOffset));
	mViewStack.active = glm::scale(
		mViewStack.active, 
		glm::vec3(xScale, TABLE_LEG_THICKNESS, zScale));
	glColor3f(0.6f, 0.4f, 0.0f);
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glutSolidCube(1.0);

	mViewStack.pop();
}
