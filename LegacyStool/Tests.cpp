#include "Tests.h"

void runTests() {
	testMatrixStack();
}


void testMatrixStack() {
	MatrixStack matStack;
	glm::mat4 test;

	// Make sure active matrix is initialized correctly
	if (matStack.active != test) {
		throw MATSTACK_INIT_ERR;
	}

	// save identity matrix and do transforms on active matrix
	matStack.push();
	matStack.active = glm::translate(matStack.active, glm::vec3(1.0f, 3.0f, 2.0f));
	matStack.active = glm::scale(matStack.active, glm::vec3(1.0f, 2.0f, 1.0f));

	// if equal, the transforms didn't work
	if (matStack.active == test) {
		cout << "bad transformation" << endl;
		throw MATSTACK_ERR;
	}

	// active matrix should now be the identity
	matStack.pop();
	if (matStack.active != test) {
		cout << "pop error" << endl;
		throw MATSTACK_ERR;
	}
}
