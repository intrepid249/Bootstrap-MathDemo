#include "Node.h"
#include <Renderer2D.h>
#include <Vector2.h>


Node::Node() {
}


Node::~Node() {
}

void Node::update(float dt) {
}

void Node::render(aie::Renderer2D * renderer) {
	// Debug render
	if (m_debugDraw) {
		Matrix3 gMat = calculateGlobalTransform();
		Vector2 pos = gMat.getTranslation();
		float rot = gMat.getRotationZ();

		renderer->drawBox(pos.x, pos.y, 5, 5, rot);
	}
}

void Node::debug(const bool flag) {
	m_debugDraw = flag;
}

void Node::setParent(Node * parent) {
	m_parent = parent;
}

Matrix3 & Node::getTransform() {
	return m_local;
}

Matrix3 Node::calculateGlobalTransform() const {
	if (m_parent == nullptr) 
		return m_local;

	return m_parent->calculateGlobalTransform() * m_local;
}

void Node::translate(const Vector2 & pos) {
	Matrix3 translation = Matrix3::createTranslation(pos);
	m_local = m_local * translation;
}

void Node::rotate(float radians) {
	Matrix3 rotation = Matrix3::createRotation(radians);
	m_local = m_local * rotation;
}

Vector2 & Node::getLocPos() {
	return m_local.getTranslation();
}

float Node::getLocRot() {
	return m_local.getRotationZ();
}
