#include "Scene.h"

Scene::Scene(int stoolCount) {
	for (int i = 0; i < stoolCount; i++) {
		int x = rand() % 120;
		int z = rand() % 120;
		Stool s(x, z);
		stools.push_back(s);
	}
}

void Scene::draw(MatrixStack &mViewStack) {

	// save previous transformation matrix
	mViewStack.push();

	// set up floor transformations
	mViewStack.active = glm::scale(
		mViewStack.active, 
		glm::vec3(SCENE_SCALE_FACTOR, SCENE_SCALE_FACTOR, SCENE_SCALE_FACTOR));
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(-60.0f, -20.0f, -60.0f));

	// draw the floor
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	floor.draw(mViewStack);

	// for each stool, position it on the floor and draw it
	for (auto i = stools.begin(); i != stools.end(); i++) {
		mViewStack.push();

		mViewStack.active = glm::translate(mViewStack.active, i->getPos());
		glLoadMatrixf(glm::value_ptr(mViewStack.active));
		i->draw(mViewStack);

		mViewStack.pop();
	}




	// restore previous transformation matrix
	mViewStack.pop();
}

void Scene::print() const {
	cout << "Scene" << endl;
	cout << "-----" << endl;
	for (auto i = stools.begin(); i != stools.end(); i++) {
		cout << "  Stool: ";
		i->print();
		cout << endl;
	}
	cout << endl;
}
