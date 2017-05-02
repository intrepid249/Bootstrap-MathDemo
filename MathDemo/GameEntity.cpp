#include <Renderer2D.h>
#include <Texture.h>


#include "OBB.h"
#include "GameEntity.h"


GameEntity::GameEntity() {
}

GameEntity::GameEntity(aie::Texture * tex) : SpriteNode(tex) {
	m_collider = std::unique_ptr<OBB>(new OBB((float)tex->getWidth(), (float)tex->getHeight()));
	m_collider->debug(true);
	m_collider->setParent(this);
}


GameEntity::~GameEntity() {
}

void GameEntity::update(float dt) {
	SpriteNode::update(dt);
	m_collider->updatePointsByMatrix((float*)getTransform());
}

void GameEntity::render(aie::Renderer2D * renderer) {
	if (m_isDrawn) {
		SpriteNode::render(renderer);
		m_collider->render(renderer);
	}
}

OBB* GameEntity::getCollider() {
	return m_collider.get();
}
