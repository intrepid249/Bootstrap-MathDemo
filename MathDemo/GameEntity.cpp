#include <Renderer2D.h>
#include <Texture.h>
#include <Vector2.h>


#include "OBB.h"
#include "GameEntity.h"


GameEntity::GameEntity() {
}

GameEntity::GameEntity(aie::Texture * tex) : SpriteNode(tex) {
	m_collider = std::unique_ptr<OBB>(new OBB((float)tex->getWidth(), (float)tex->getHeight()));
	m_collider->setParent(this);
}


GameEntity::~GameEntity() {
}

void GameEntity::update(float dt) {
	SpriteNode::update(dt);
	m_collider->updatePointsByMatrix((float*)&getTransform());
}

void GameEntity::render(aie::Renderer2D * renderer) {
	if (m_isDrawn) {
		SpriteNode::render(renderer);
		m_collider->render(renderer);
	}
}

void GameEntity::renderStaticRotation(aie::Renderer2D * renderer) {
	Matrix3<float> gMat = calculateGlobalTransform();
	Vector2<float> scale = Vector2<float>(gMat[0].magnitude(), gMat[1].magnitude());
	Vector2<float> pos = gMat.getTranslation();
	float rot = getStaticRotation();

	renderer->drawSprite(m_sprite, pos.x, pos.y, scale.x * m_size.x, scale.x * m_size.y, rot, 0, m_origin.x, m_origin.y);

	Node::render(renderer);
}

OBB* GameEntity::getCollider() {
	return m_collider.get();
}

void GameEntity::setStaticRotation(float angle) {
	m_staticRotation = angle;
}

float GameEntity::getStaticRotation() {
	return m_staticRotation;
}