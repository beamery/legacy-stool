#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "Tests.h"
#include "Scene.h"

using namespace std;

struct WindowData
{
	GLint height, width;
	GLint handle;
	bool wireframe;
} window;

void DisplayFunc()
{
	// How long have we been running (in seconds)?
	float time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;

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
	glm::mat4 projection_matrix = glm::perspective(30.0f, float(window.width) / float(window.height), 1.0f, 10.0f);
	glLoadMatrixf(glm::value_ptr(projection_matrix));

	glMatrixMode(GL_MODELVIEW);

	/* These lines:
		glLoadIdentity();
		glTranslated(0, 0, -5);
		glRotated(time * 90.0, 0, 1, 0);
	   are identical in effect to these next three lines.
	*/
	glm::mat4 modelview_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	modelview_matrix = glm::rotate(modelview_matrix, time * 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));

	// This is a sample of using the glu Quadrics - you can draw any number of Quadrics using 
	// the same GLUquadric structure. Remember to delete it when you're finished.
	GLUquadric * q = gluNewQuadric();
	glColor3d(1, 0, 0);
	gluCylinder(q, 2.0, 0.0, 2.0, 30, 3);
	glColor3d(0, 0, 1);
	gluSphere(q, 1.0, 30, 30);
	gluDeleteQuadric(q);

	// Show an example of using a glut built-in shape. Note how I use the matrix to 
	// alter the drawn shape of a 1 unit cube.
	glColor3d(0.8706, 0.7126, 0.5294);
	modelview_matrix = glm::scale(modelview_matrix, glm::vec3(2.5f, 0.25f, 0.25f));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	glutSolidCube(1);

	glutSwapBuffers();
	glutPostRedisplay();
}

void ReshapeFunc(GLint w, GLint h)
{
	if (h > 0)
	{
		window.height = h;
		window.width = w;
	}
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'w':
		window.wireframe = !window.wireframe;
		break;

	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

int main(int argc, char * argv[])
{
	runTests();

	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window.width , window.height);
	window.handle = glutCreateWindow("Hello World - try the 'w' key");
	window.wireframe = false;
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);

	glutMainLoop();
}
