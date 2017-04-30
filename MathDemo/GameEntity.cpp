#include <Renderer2D.h>
#include <Texture.h>
#include <memory>

#include "AABB.h"
#include "GameEntity.h"


GameEntity::GameEntity() {
}

GameEntity::GameEntity(aie::Texture * tex) : SpriteNode(tex) {
	collider = std::unique_ptr<AABB>(new AABB(getLocPos().x, getLocPos().y, tex->getWidth(), tex->getHeight()));
	collider->debug(true);
	collider->setParent(this);
}


GameEntity::~GameEntity() {
}

void GameEntity::update(float dt) {
	SpriteNode::update(dt);
	collider->updateSizeByRotation(getLocRot());
}

void GameEntity::render(aie::Renderer2D * renderer) {
	SpriteNode::render(renderer);
	collider->render(renderer);
}
