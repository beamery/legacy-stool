#ifndef UTILS_H
#define UTILS_H

#define BLADE_LENGTH 8.0f

#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Constants.h"

/* draws a variation on a disk, but with a height parameter which can be
 * adjusted to turn it into a cone without a point. 
 * 
 * used to draw bottom of stool seat and base of fan
 */
void drawSkewedDisk(MatrixStack &mViewStack, float lowerRad, float upperRad, 
	float height, int slices);

/* 
 * draws a pinwheel with the given number of blades. 
 * 
 * used to draw the fan blades
 */
void drawPinwheel(MatrixStack &mViewStack, float rotation, int blades, glm::vec3 colors[]);

#endif