#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "Tests.h"
#include "Scene.h"
#include "MatrixStack.h"

#define DEFAULT_FOV 50.0f
#define CAMERA_DIST 4.0f
#define CAMERA_HEIGHT 1.0f
#define CAMERA_ZNEAR 0.5f
#define CAMERA_ZFAR 5.0f

using namespace std;

void DrawCamera(MatrixStack &mViewStack);
void DrawFrustum(MatrixStack &mViewStack);

struct WindowData {
	GLint height, width;
	GLint handle;
	bool wireframe, tableRender;
	float fov, rotX, rotY, aspect;
} fpWin;
WindowData tpWin;

Scene scene(1);
MatrixStack mViewStack;
const float PI = atan(1) * 4.0f;

void DisplayFunc() {
	// How long have we been running (in seconds)?
	float time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, fpWin.wireframe ? GL_LINE : GL_FILL);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, fpWin.width, fpWin.height);
	glMatrixMode(GL_PROJECTION);

	fpWin.aspect = float(fpWin.width) / float(fpWin.height);
	glm::mat4 projection_matrix = glm::perspective(
		fpWin.fov, fpWin.aspect, CAMERA_ZNEAR, CAMERA_ZFAR);
	glLoadMatrixf(glm::value_ptr(projection_matrix));

	glMatrixMode(GL_MODELVIEW);

	mViewStack.push();

	// set up basic camera position and orientation
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, -CAMERA_DIST));

	// user controlled rotations
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotY, glm::vec3(0.0f, 1.0f, 0.0f));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	scene.draw(mViewStack, fpWin.tableRender);

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

	glm::mat4 projection_matrix = glm::perspective(
		tpWin.fov, float(tpWin.width) / float(tpWin.height), 1.0f, 100.0f);
	glLoadMatrixf(glm::value_ptr(projection_matrix));

	glMatrixMode(GL_MODELVIEW);

	mViewStack.push();

	// position entire system
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, -1.0f, -2.5 * CAMERA_DIST));

	// perform camera rotations
	mViewStack.active = glm::rotate(mViewStack.active, -fpWin.rotY, glm::vec3(0.0f, 1.0f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, -fpWin.rotX, glm::vec3(1.0f, 0.0f, 0.0f));

	mViewStack.push();
	// pull the camera back from the scene
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, CAMERA_DIST));
	DrawCamera(mViewStack);
	DrawFrustum(mViewStack);
	mViewStack.pop();

	// reverse camera rotations for the scene (allows it to be statically oriented)
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, fpWin.rotY, glm::vec3(0.0f, 1.0f, 0.0f));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	scene.draw(mViewStack, fpWin.tableRender);

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
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, 3.0f));

	// draw axes
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glBegin(GL_LINES);
	// x
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	// y
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	// z
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();


	mViewStack.active = glm::scale(mViewStack.active, glm::vec3(1.0f, 1.0f, 2.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
	glutSolidCube(3);
	mViewStack.pop();
}

void DrawFrustum(MatrixStack &mViewStack) {
	mViewStack.push();
	float fovRadians = fpWin.fov * (2 * PI / 360);
	//cout << fovRadians / PI << endl;

	float yNear = CAMERA_ZNEAR * tan(fovRadians / 2);
	float xNear = fpWin.aspect * yNear;
	float yFar = CAMERA_ZFAR * tan(fovRadians / 2);
	float xFar = fpWin.aspect * yFar;

	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(xNear, yNear, -CAMERA_ZNEAR);
	glVertex3f(-xNear, yNear, -CAMERA_ZNEAR);
	glVertex3f(-xNear, -yNear, -CAMERA_ZNEAR);
	glVertex3f(xNear, -yNear, -CAMERA_ZNEAR);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(xFar, yFar, -CAMERA_ZFAR);
	glVertex3f(-xFar, yFar, -CAMERA_ZFAR);
	glVertex3f(-xFar, -yFar, -CAMERA_ZFAR);
	glVertex3f(xFar, -yFar, -CAMERA_ZFAR);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xFar, yFar, -CAMERA_ZFAR);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-xFar, yFar, -CAMERA_ZFAR);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-xFar, -yFar, -CAMERA_ZFAR);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xFar, -yFar, -CAMERA_ZFAR);
	glEnd();

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
	case 't':
		fpWin.tableRender = !fpWin.tableRender;
		break;
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
	fpWin.tableRender = false;
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	tpWin.fov = DEFAULT_FOV;
	tpWin.rotX = 0.0f;
	tpWin.rotY = 0.0f;
	tpWin.handle = glutCreateWindow("Legacy Stool - Third Person");
	glutDisplayFunc(TPDisplayFunc);
	glutReshapeFunc(TPReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	glutMainLoop();
}
