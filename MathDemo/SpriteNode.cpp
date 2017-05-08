#include "SpriteNode.h"
#include <Texture.h>
#include <Renderer2D.h>

SpriteNode::SpriteNode() {
}

SpriteNode::SpriteNode(aie::Texture *m_tex) : m_sprite(m_tex), m_size(Vector2<float>((float)m_tex->getWidth(), (float)m_tex->getHeight())) {
}


SpriteNode::~SpriteNode() {
}

void SpriteNode::renderStaticRotation(aie::Renderer2D * renderer) {
	Matrix3<float> gMat = calculateGlobalTransform();
	Vector2<float> scale = Vector2<float>(gMat[0].magnitude(), gMat[1].magnitude());
	Vector2<float> pos = gMat.getTranslation();
	float rot = gMat.getRotationZ();

	renderer->drawSprite(m_sprite, pos.x, pos.y, scale.x * m_size.x, scale.x * m_size.y, rot, 0, m_origin.x, m_origin.y);

	Node::render(renderer);
}

void SpriteNode::render(aie::Renderer2D * renderer) {
	Matrix3<float> gMat = calculateGlobalTransform();

	renderer->drawSpriteTransformed3x3(m_sprite, (float*)gMat, m_size.x, m_size.y, 0, m_origin.x, m_origin.y);

	Node::render(renderer);
}

void SpriteNode::setSize(const Vector2<float> & size) {
	m_size = size;
}

Vector2<float> & SpriteNode::getSize() {
	return m_size;
}

void SpriteNode::setOrigin(const Vector2<float> &origin) {
	m_origin = origin;
}

Vector2<float> & SpriteNode::getOrigin() {
	return m_origin;
}
