#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Scene.h"
#include "Error.h"

using namespace std;

void runTests();

void testMatrixStack();
void testScene();
void glmMatrixTest();


#endif