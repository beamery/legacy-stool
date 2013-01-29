#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Tests.h"
#include "MatrixStack.h"
#include "Floor.h"

using namespace std;

struct WindowData {
	GLint height, width;
	GLint handle;
} window;

struct Camera {
	GLdouble xRot, yRot;
} camera;


MatrixStack modelStack;
Floor worldFloor;

void displayFunc() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glMatrixMode(GL_PROJECTION);

	glm::mat4 projection_matrix = glm::perspective(30.0f, float(window.width) / float(window.height), 1.0f, 10.0f);
	glLoadMatrixf(glm::value_ptr(projection_matrix));

	glViewport(0, 0, window.width, window.height);
	glMatrixMode(GL_MODELVIEW);

	modelStack.push();

	// Camera transform
	modelStack.active = glm::translate(modelStack.active, glm::vec3(0.0f, 0.0f, -5.0f));
	modelStack.active = glm::rotate(modelStack.active, float(camera.xRot), glm::vec3(1.0f, 0.0f, 0.0f));
	modelStack.active = glm::rotate(modelStack.active, float(camera.yRot), glm::vec3(0.0f, 1.0f, 0.0f));

	glLoadMatrixf(glm::value_ptr(modelStack.active));

	worldFloor.draw(modelStack);


	GLUquadric *c = gluNewQuadric();

	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(c, 0.2, 0.0, 0.2, 16, 16);

	modelStack.pop();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshapeFunc(GLint w, GLint h) {

	if (h > 0) {
		window.height = h;
		window.width = w;
	}
}

void keyboardFunc(unsigned char c, int x, int y) {

	switch (c) {
	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	case 'w':
		camera.xRot += 2;
		return;
	case 's':
		camera.xRot -= 2;
		return;
	case 'd':
		camera.yRot -= 2;
		return;
	case 'a':
		camera.yRot += 2;
		return;
	}
}


int main(int argc, char * argv[]) {
	runTests();

	camera.xRot = 0;
	camera.yRot = 0;

	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window.width , window.height);
	window.handle = glutCreateWindow("Legacy Stool");
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);

	glutMainLoop();
}
