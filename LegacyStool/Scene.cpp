#include "Scene.h"

Scene::Scene(/*int stoolCount*/) : 
	table(Table(glm::vec3(60.0f, 0.0f, 60.0f))) {

	//if (stoolCount >= 1) {
		stools.push_back(
			Stool(glm::vec3(60.0f + STOOL_OFFSET, 0.0f, 60.0f)));
		stools.push_back(
			Stool(glm::vec3(60.0f - STOOL_OFFSET, 0.0f, 60.0f)));
		stools.push_back(
			Stool(glm::vec3(60.0f, 0.0f, 60.0f + STOOL_OFFSET)));
		stools.push_back(
			Stool(glm::vec3(60.0f, 0.0f, 60.0f - STOOL_OFFSET)));
		stools.push_back(
			Stool(glm::vec3(100.0f, 0.0f, 100.0f)));
	//}

	// large vase
	vases.push_back(Vase(glm::vec3(10.0f, 0.0f, 10.0f), 
		14.0f, 2.5f, 1.0f, 2 * PI / 14.0f, 0.0f, 20, 10));

	// wide bowl
	vases.push_back(Vase(glm::vec3(-12.0f, 0.0f, 8.0f), 
		4.0f, 3.0f, 3.0f, 2 * PI / 14.0f, 0.0f, 20, 10));

	// goblet
	vases.push_back(Vase(glm::vec3(6.0f, 0.0f, -10.0f), 
		6.0f, 1.5f, 1.0f, 2 * PI / 8.0f, 4.0f, 20, 10));

	/*for (int i = 0; i < stoolCount - 1; i++) {
		float x = float(rand() % int(floor(110 - LEG_HORIZ_OFFSET)));
		float z = float(rand() % int(floor(110 - LEG_HORIZ_OFFSET)));
		Stool s(glm::vec3(x, 0.0f, z));
		stools.push_back(s);
	}*/
}

void Scene::draw(MatrixStack &mViewStack, bool hasTable) {

	// save previous transformation matrix
	mViewStack.push();

	// set up floor transformations
	mViewStack.active = glm::scale(mViewStack.active, 
		glm::vec3(INCHES_PER_WORLD_UNIT, INCHES_PER_WORLD_UNIT, INCHES_PER_WORLD_UNIT));
	mViewStack.active = glm::translate(mViewStack.active, 
		glm::vec3(-60.0f, -36.0f, -60.0f));

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

	// optionally draw a table and some vases on top of it
	if (hasTable) {
		mViewStack.push();
		mViewStack.active = glm::translate(mViewStack.active, table.getPos());
		table.draw(mViewStack);

		// move the bottom of the vase up to the table top
		mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, TABLE_HEIGHT, 0.0f));

		//glEnable(GL_BLEND);

		// draw vases
		for (auto i = vases.begin(); i != vases.end(); i++) {
			mViewStack.push();
			mViewStack.active = glm::translate(mViewStack.active, i->getPos());
			i->draw(mViewStack);
			mViewStack.pop();
		}
		//glDisable(GL_BLEND);
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
