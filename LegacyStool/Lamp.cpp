#include "Lamp.h"

const float PI = float(atan(1)) * 4.0f;

void Lamp::draw(MatrixStack &mViewStack) {
	mViewStack.push();

	// do lamp translations

	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	drawBase(mViewStack);

	mViewStack.pop();
}

#define LAMP_VSTEP_SIZE 0.5f
#define LAMP_RSTEP_SIZE 0.1f * PI
void Lamp::drawBase(MatrixStack &mViewStack) {
	float radius = 1.0f;

	mViewStack.push();

	mViewStack.active = glm::scale(mViewStack.active, glm::vec3(5.0f, 5.0f, 5.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor3f(0.8f, 0.5f, 0.5f);
	for (float y = 0; y < 2.0f; y += LAMP_VSTEP_SIZE) {
		glBegin(GL_TRIANGLE_STRIP);
		for (float theta = 0; theta <= 2 * PI; theta += LAMP_RSTEP_SIZE) {
			glVertex3f(sin(theta), y, cos(theta));
			glVertex3f(sin(theta), y + LAMP_VSTEP_SIZE, cos(theta));
		}
		// two more vertices at beginning for continuity
		glVertex3f(sin(0), y, cos(0));
		glVertex3f(sin(0), y + LAMP_VSTEP_SIZE, cos(0));
		glEnd();
	}

	mViewStack.pop();
}
