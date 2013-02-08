#include "Tests.h"

void runTests() {
	testMatrixStack();
	testScene();
	glmMatrixTest();
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

void testScene() {
	Scene s;
	s.print();
}

void glmMatrixTest() {
	// It appears that m[i] gives column i
	glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << m[j][i] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	m[0] = glm::vec4(4.0f, 3.0f, 7.0f, 0.0f);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << m[j][i] << "\t";
		}
		cout << endl;
	}
}
