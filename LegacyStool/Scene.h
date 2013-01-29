#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Stool.h"
#include "Floor.h"

using namespace std;

// Contains the whole scene to be drawn
class Scene {

public:
	// Initialize scene with the given number of stools
	Scene(int stoolCount);

	// Draw the whole scene (floor, stools)
	void draw(MatrixStack &mViewStack);

	// Print the stools contained in this scene
	void print() const;

private:
	Floor floor;
	vector<Stool> stools;
};


#endif