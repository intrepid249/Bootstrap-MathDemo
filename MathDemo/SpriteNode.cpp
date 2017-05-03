#include "SpriteNode.h"
#include <Texture.h>
#include <Renderer2D.h>

SpriteNode::SpriteNode() {
}

SpriteNode::SpriteNode(aie::Texture *m_tex) : m_sprite(m_tex), m_size(Vector2((float)m_tex->getWidth(), (float)m_tex->getHeight())) {
}


SpriteNode::~SpriteNode() {
}

void SpriteNode::render(aie::Renderer2D * renderer) {
	Matrix3 gMat = calculateGlobalTransform();

	//change this to use drawSprite so we have the option of splitting the child's rotation
	renderer->drawSpriteTransformed3x3(m_sprite, (float*)gMat, m_size.x, m_size.y, 0, m_origin.x, m_origin.y);

	Node::render(renderer);
}

void SpriteNode::renderByMatrix(aie::Renderer2D * renderer, float *mat) {
	renderer->drawSpriteTransformed3x3(m_sprite, (float*)mat, m_size.x, m_size.y, 0, m_origin.x, m_origin.y);

	Node::render(renderer);
}

void SpriteNode::setSize(const Vector2 & size) {
	m_size = size;
}

Vector2 & SpriteNode::getSize() {
	return m_size;
}

void SpriteNode::setOrigin(const Vector2 &origin) {
	m_origin = origin;
}

Vector2 & SpriteNode::getOrigin() {
	return m_origin;
}
