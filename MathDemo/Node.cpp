#include "Node.h"
#include <Renderer2D.h>
#include "OBB.h"

Node::Node() {
}


Node::~Node() {
}

void Node::update(float dt) {
}

void Node::render(aie::Renderer2D * renderer) {
	// Debug render
	#ifdef _DEBUG
		Matrix3<float> gMat = calculateGlobalTransform();
		Vector2<float> pos = gMat.getTranslation();
		float rot = gMat.getRotationZ();

		renderer->drawBox(pos.x, pos.y, 5, 5, rot);
	#endif // _DEBUG
}

OBB * Node::getCollider() {
	// Just make this empty so child classes can call it
	return nullptr;
}

//bool Node::checkCollision(std::vector<Node*> objects) {
//	return false;
//}

void Node::setParent(Node * parent) {
	m_parent = parent;
}

void Node::setDrawn(bool flag) {
	m_isDrawn = flag;
}

bool Node::isDrawn() {
	return m_isDrawn;
}

Matrix3<float> & Node::getTransform() {
	return m_local;
}

Matrix3<float> Node::calculateGlobalTransform() const {
	if (m_parent == nullptr)
		return m_local;

	return m_parent->calculateGlobalTransform() * m_local;
}

void Node::scale(const Vector2<float> &size) {
	Matrix3<float> scale = Matrix3<float>::createScale(size.x, size.y);
	m_local = m_local * scale;
}

void Node::translate(const Vector2<float> & pos) {
	Matrix3<float> translation = Matrix3<float>::createTranslation(pos);
	m_local = m_local * translation;
}

void Node::rotate(float radians) {
	Matrix3<float> rotation = Matrix3<float>::createRotation(radians);
	m_local = m_local * rotation;
}

void Node::setRotate(float radians) {
	m_local.setRotateZ(radians);
}

Vector2<float> Node::getLocPos() {
	return m_local.getTranslation();
}

float Node::getLocRot() {
	return m_local.getRotationZ();
}
