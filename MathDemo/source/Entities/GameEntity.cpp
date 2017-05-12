#include <Renderer2D.h>
#include <Texture.h>
#include <Vector2.h>


#include "Colliders/OBB.h"
#include "Entities/GameEntity.h"


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
	m_collider->updatePointsByMatrix((float*)&calculateGlobalTransform());
}

void GameEntity::render(aie::Renderer2D * renderer) {
	if (m_isDrawn) {
		SpriteNode::render(renderer);
		m_collider->render(renderer);
	}
}

//bool GameEntity::checkCollision(std::vector<Node*> objects) {
//	for (size_t i = 0; i < objects.size(); ++i) {
//		if (getCollider()->collides(*objects[i]->getCollider())) return true;
//	}
//	return false;
//}

OBB* GameEntity::getCollider() {
	return m_collider.get();
}