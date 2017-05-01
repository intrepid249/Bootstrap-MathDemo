#include "OBB.h"
#include <Vector2.h>


OBB::OBB() {}

OBB::OBB(float width, float height) : m_size(Vector2(width, height)) {}


OBB::~OBB() {}

bool OBB::contains(Vector2 & point) {
	return false;
}

bool OBB::collides(OBB & rhs) {
	return false;
}
