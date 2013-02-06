#ifndef LAMP_H
#define LAMP_H

#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"

#define LAMP_HEIGHT 18.0f

class Lamp {
public:
	Lamp() {}
	void draw(MatrixStack &mViewStack);

private:
	void drawBase(MatrixStack &mViewStack);

};


#endif