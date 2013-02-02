#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "Tests.h"
#include "Scene.h"
#include "MatrixStack.h"

#define DEFAULT_FOV 30.0f
#define CAMERA_DIST 1.9f

using namespace std;

void DrawCamera(MatrixStack &mViewStack);

struct WindowData {
	GLint height, width;
	GLint handle;
	bool wireframe;
	float fov, rotX, rotY;
} fpWin;

WindowData tpWin;

Scene scene(0);
MatrixStack mViewStack;

void DisplayFunc() {
	// How long have we been running (in seconds)?
	float time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, fpWin.wireframe ? GL_LINE : GL_FILL);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, fpWin.width, fpWin.height);
	glMatrixMode(GL_PROJECTION);

	glm::mat4 projection_matrix = glm::perspective(fpWin.fov, float(fpWin.width) / float(fpWin.height), 1.0f, 10.0f);
	glLoadMatrixf(glm::value_ptr(projection_matrix));

	glMatrixMode(GL_MODELVIEW);

	mViewStack.push();

	// set up basic camera position and orientation
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, -CAMERA_DIST));

	// user controlled rotations
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotY, glm::vec3(0.0f, 1.0f, 0.0f));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	scene.draw(mViewStack);

	mViewStack.pop();

	glutSwapBuffers();
	glutPostRedisplay();
}


void TPDisplayFunc() {
	// How long have we been running (in seconds)?
	float time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, fpWin.wireframe ? GL_LINE : GL_FILL);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, tpWin.width, tpWin.height);
	glMatrixMode(GL_PROJECTION);

	glm::mat4 projection_matrix = glm::perspective(tpWin.fov, float(tpWin.width) / float(tpWin.height), 1.0f, 100.0f);
	glLoadMatrixf(glm::value_ptr(projection_matrix));

	glMatrixMode(GL_MODELVIEW);

	mViewStack.push();

	// position entire system
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -1.0f, -3 * CAMERA_DIST));

	// perform camera rotations
	mViewStack.active = glm::rotate(mViewStack.active, -fpWin.rotY, glm::vec3(0.0f, 1.0f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, -fpWin.rotX, glm::vec3(1.0f, 0.0f, 0.0f));

	mViewStack.push();
	// pull the camera back from the scene
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, CAMERA_DIST));
	DrawCamera(mViewStack);
	mViewStack.pop();

	// reverse camera rotations for the scene (allows it to be statically oriented)
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotY, glm::vec3(0.0f, 1.0f, 0.0f));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	scene.draw(mViewStack);

	mViewStack.pop();

	glutSwapBuffers();
	glutPostRedisplay();
}

/*
 * Draws camera. Camera transformations in this function are specified in inches.
 */
void DrawCamera(MatrixStack &mViewStack) {
	mViewStack.push();
	mViewStack.active = glm::scale(mViewStack.active, 
		glm::vec3(INCHES_PER_WORLD_UNIT, INCHES_PER_WORLD_UNIT, INCHES_PER_WORLD_UNIT));

	// draw axes
	glBegin(GL_LINES);
	// x
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, 0.0f);
	// y
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 15.0f, 0.0f);
	// z
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 15.0f);
	glEnd();

	mViewStack.active = glm::scale(mViewStack.active, glm::vec3(1.0f, 1.0f, 2.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor4f(0.6f, 0.6f, 1.0f, 1.0f);
	glutSolidCube(5);
	mViewStack.pop();
}




void ReshapeFunc(GLint w, GLint h) {
	if (h > 0) {
		fpWin.height = h;
		fpWin.width = w;
	}
}

void TPReshapeFunc(GLint w, GLint h) {
	if (h > 0) {
		tpWin.height = h;
		tpWin.width = w;
	}
}


void KeyboardFunc(unsigned char c, int x, int y) {
	switch (c) {
	case 'i':
		fpWin.fov--;
		break;
	case 'o':
		fpWin.fov++;
		break;
	case 'j':
		scene.adjustStoolHeights(-0.1f);
		break;
	case 'k':
		scene.adjustStoolHeights(0.1f);
		break;
	case 'w':
		fpWin.wireframe = !fpWin.wireframe;
		break;
	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

void SpecialFunc(int c, int x, int y) {
	switch (c) {
	case GLUT_KEY_UP:
		fpWin.rotX++;
		fpWin.rotX = min(fpWin.rotX + 1, 89.0f);
		break;
	case GLUT_KEY_DOWN:
		fpWin.rotX--;
		fpWin.rotX = max(fpWin.rotX - 1, -89.0f);
		break;
	case GLUT_KEY_LEFT:
		fpWin.rotY++;
		break;
	case GLUT_KEY_RIGHT:
		fpWin.rotY--;
		break;
	}
}

int main(int argc, char * argv[]) {
	fpWin.fov = DEFAULT_FOV;
	fpWin.rotX = 0.0f;
	fpWin.rotY = 0.0f;
	runTests();

	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(fpWin.width , fpWin.height);
	fpWin.handle = glutCreateWindow("Legacy Stool - First Person");
	fpWin.wireframe = false;
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	tpWin.fov = DEFAULT_FOV;
	tpWin.rotX = 0.0f;
	tpWin.rotY = 0.0f;
	fpWin.handle = glutCreateWindow("Legacy Stool - Third Person");
	fpWin.wireframe = false;
	glutDisplayFunc(TPDisplayFunc);
	glutReshapeFunc(TPReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	glutMainLoop();
}
