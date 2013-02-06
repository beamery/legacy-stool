#ifndef SCENE_H
#define SCENE_H

#define INCHES_PER_WORLD_UNIT 0.03f
#define STOOL_OFFSET 30.0f

#include <iostream>
#include <vector>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Stool.h"
#include "Floor.h"
#include "Table.h"
#include "Lamp.h"

using namespace std;

// Contains the whole scene to be drawn
class Scene {

public:
	// Initialize scene with the given number of stools
	Scene(int stoolCount);

	// Draw the whole scene (floor, stools)
	void draw(MatrixStack &mViewStack, bool hasTable = false);

	void adjustStoolHeights(float amount);

	// Print the stools contained in this scene
	void print() const;

private:
	Floor sceneFloor;
	vector<Stool> stools;
	Table table;
	Lamp lamp;
};


#endif