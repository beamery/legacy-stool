#include "Scene.h"

Scene::Scene(int stoolCount)
{
	for (int i = 0; i < stoolCount; i++) {
		Stool s(i, i*i);
		stools.push_back(s);
	}
}

void Scene::draw(MatrixStack &mViewStack) {

	// save previous transformation matrix
	mViewStack.push();

	// set up floor transformations

	// draw the floor
	floor.draw(mViewStack);

	// for each stool, position it on the floor and draw it


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
