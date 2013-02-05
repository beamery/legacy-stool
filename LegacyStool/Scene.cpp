#include "Scene.h"

Scene::Scene(int stoolCount) : 
	table(Table(glm::vec3(60.0f, 0.0f, 60.0f))) {

	if (stoolCount >= 1) {
		stools.push_back(
			Stool(glm::vec3(60.0f + STOOL_OFFSET, 0.0f, 60.0f)));
		stools.push_back(
			Stool(glm::vec3(60.0f - STOOL_OFFSET, 0.0f, 60.0f)));
		stools.push_back(
			Stool(glm::vec3(60.0f, 0.0f, 60.0f + STOOL_OFFSET)));
		stools.push_back(
			Stool(glm::vec3(60.0f, 0.0f, 60.0f - STOOL_OFFSET)));
		stools.push_back(
			Stool(glm::vec3(20.0f, 0.0f, 20.0f)));
	}

	for (int i = 0; i < stoolCount - 1; i++) {
		float x = float(rand() % int(floor(110 - LEG_HORIZ_OFFSET)));
		float z = float(rand() % int(floor(110 - LEG_HORIZ_OFFSET)));
		Stool s(glm::vec3(x, 0.0f, z));
		stools.push_back(s);
	}
}

void Scene::draw(MatrixStack &mViewStack, bool hasTable) {

	// save previous transformation matrix
	mViewStack.push();

	// set up floor transformations
	mViewStack.active = glm::scale(mViewStack.active, 
		glm::vec3(INCHES_PER_WORLD_UNIT, INCHES_PER_WORLD_UNIT, INCHES_PER_WORLD_UNIT));
	mViewStack.active = glm::translate(mViewStack.active, 
		glm::vec3(-60.0f, 0.0f, -60.0f));

	// draw the floor
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	sceneFloor.draw(mViewStack);

	// for each stool, position it on the floor and draw it
	for (auto i = stools.begin(); i != stools.end(); i++) {
		mViewStack.push();

		mViewStack.active = glm::translate(mViewStack.active, i->getPos());
		i->draw(mViewStack);

		mViewStack.pop();
	}

	// optionally draw a table
	if (hasTable) {
		mViewStack.push();
		mViewStack.active = glm::translate(mViewStack.active, table.getPos());
		table.draw(mViewStack);
		mViewStack.pop();
	}

	// restore previous transformation matrix
	mViewStack.pop();
}

void Scene::adjustStoolHeights(float amount) {
	for (auto i = stools.begin(); i != stools.end(); i++) {
		i->adjustHeight(amount);
	}
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
