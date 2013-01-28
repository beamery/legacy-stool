#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

using namespace std;

struct WindowData {
	GLint height, width;
	GLint handle;
} window;

struct Disk {
	GLdouble xRot, yRot;
} disk;


void DisplayFunc() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glm::mat4 projection_matrix = glm::perspective(30.0f, float(window.width) / float(window.height), 1.0f, 10.0f);
	glLoadMatrixf(glm::value_ptr(projection_matrix));
	//glLoadIdentity();
	//gluPerspective(30, double(window.width) / double(window.height), 1, 10);

	glViewport(0, 0, window.width, window.height);
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 modelview_matrix;

	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, -5.0f));
	modelview_matrix = glm::rotate(modelview_matrix, float(disk.xRot), glm::vec3(1.0f, 0.0f, 0.0f));
	modelview_matrix = glm::rotate(modelview_matrix, float(disk.yRot), glm::vec3(0.0f, 1.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	//glLoadIdentity();
	//glTranslated(0, 0, -5);

	GLUquadric *d = gluNewQuadric();
	gluCylinder(d, 0.2, 0.2, 1, 64, 64);

	glutSwapBuffers();
	glutPostRedisplay();
}

void ReshapeFunc(GLint w, GLint h) {

	if (h > 0) {
		window.height = h;
		window.width = w;
	}
}

void KeyboardFunc(unsigned char c, int x, int y) {

	switch (c) {
	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	case 'w':
		disk.xRot += 10;
		return;
	case 's':
		disk.xRot -= 10;
		return;
	case 'd':
		disk.yRot += 10;
		return;
	case 'a':
		disk.yRot -= 10;
		return;
	}
}

int main(int argc, char * argv[]) {

	disk.xRot = 0;
	disk.yRot = 0;

	cout << "Hello World" << endl;
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(window.width , window.height);
	window.handle = glutCreateWindow("Hello World");
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);

	glutMainLoop();
}
