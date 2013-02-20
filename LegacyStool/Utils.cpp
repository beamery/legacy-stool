#include "Utils.h"

void drawSkewedDisk(MatrixStack &mViewStack, float lowerRad, float upperRad, 
						   float height, int slices) {
	mViewStack.push();

	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	// Specify color outside function
	//glColor4f(0.1f, 0.4f, 0.4f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	for (float theta = 0; theta <= 2 * PI; theta +=  2 * PI / slices) {
		glVertex3f(lowerRad * cos(theta), -height, lowerRad * sin(theta));
		glVertex3f(upperRad * cos(theta), 0.0f, upperRad * sin(theta));
	}
	// two more vertices at beginning for continuity
		glVertex3f(lowerRad * cos(0.0f), -height, lowerRad * sin(0.0f));
		glVertex3f(upperRad * cos(0.0f), 0.0f, upperRad * sin(0.0f));
	glEnd();
	mViewStack.pop();
}

void drawPinwheel(MatrixStack &mViewStack, float rotation, int blades, glm::vec3 colors[]) {
	mViewStack.push();


	// Set rotation of entire pinwheel
	mViewStack.active = glm::rotate(mViewStack.active, rotation, glm::vec3(0.0f, 1.0f, 0.0f));

	// draw individual blades
	for (int i = 0; i < blades; i++) {
		glColor3f(colors[i].r, colors[i].g, colors[i].b);

		mViewStack.active = glm::rotate(mViewStack.active, 360.0f / blades, 
			glm::vec3(0.0f, 1.0f, 0.0f));

		glLoadMatrixf(glm::value_ptr(mViewStack.active));
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(BLADE_LENGTH, -1.0f, 5.0f);
		glVertex3f(3 * BLADE_LENGTH / 4.0f, 0.0f, -0.0f);
		glEnd();

	}



	mViewStack.pop();
}
