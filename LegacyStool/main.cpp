#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "Tests.h"
#include "Scene.h"
#include "MatrixStack.h"

#define DEFAULT_FOV 30.0f

using namespace std;

struct WindowData {
	GLint height, width;
	GLint handle;
	bool wireframe;
	float fov, rotX, rotY;
} window;

Scene scene(0);
MatrixStack mViewStack;

void DisplayFunc() {
	// How long have we been running (in seconds)?
	float time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, window.wireframe ? GL_LINE : GL_FILL);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window.width, window.height);
	glMatrixMode(GL_PROJECTION);

	/* These lines:
		glLoadIdentity();
		gluPerspective(30, double(window.width) / double(window.height), 1, 10);
	   are identical in effect to these next two lines.
	*/
	glm::mat4 projection_matrix = glm::perspective(window.fov, float(window.width) / float(window.height), 1.0f, 10.0f);
	glLoadMatrixf(glm::value_ptr(projection_matrix));

	glMatrixMode(GL_MODELVIEW);

	/* These lines:
		glLoadIdentity();
		glTranslated(0, 0, -5);
		glRotated(time * 90.0, 0, 1, 0);
	   are identical in effect to these next three lines.
	*/
	mViewStack.push();

	// set up basic camera position and orientation
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, -5.0f));
	//mViewStack.active = glm::rotate(mViewStack.active, time * 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// user controlled rotations
	mViewStack.active = glm::rotate(mViewStack.active, window.rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	mViewStack.active = glm::rotate(mViewStack.active, window.rotY, glm::vec3(0.0f, 1.0f, 0.0f));

	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	scene.draw(mViewStack);

	mViewStack.pop();

	glutSwapBuffers();
	glutPostRedisplay();
}

void ReshapeFunc(GLint w, GLint h) {
	if (h > 0)
	{
		window.height = h;
		window.width = w;
	}
}

void KeyboardFunc(unsigned char c, int x, int y) {
	switch (c) {
	case 'i':
		window.fov--;
		break;
	case 'o':
		window.fov++;
		break;
	case 'j':
		scene.adjustStoolHeights(-0.1f);
		break;
	case 'k':
		scene.adjustStoolHeights(0.1f);
		break;
	case 'w':
		window.wireframe = !window.wireframe;
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
		window.rotX++;
		window.rotX = min(window.rotX + 1, 89.0f);
		break;
	case GLUT_KEY_DOWN:
		window.rotX--;
		window.rotX = max(window.rotX - 1, -89.0f);
		break;
	case GLUT_KEY_LEFT:
		window.rotY++;
		break;
	case GLUT_KEY_RIGHT:
		window.rotY--;
		break;
	}
}

int main(int argc, char * argv[]) {
	window.fov = DEFAULT_FOV;
	window.rotX = 20.0f;
	window.rotY = 0.0f;
	runTests();

	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window.width , window.height);
	window.handle = glutCreateWindow("Hello World - try the 'w' key");
	window.wireframe = false;
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	glutMainLoop();
}
