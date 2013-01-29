#include "Stool.h"

Stool::Stool(float x, float z)  {
	pos = glm::vec3(x, 0.0f, z);
}

glm::vec3 Stool::getPos() const{
	return pos;
}

void Stool::draw(MatrixStack &mViewStack) {

}

void Stool::print() const {
	cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")";
}
