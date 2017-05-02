#include <Renderer2D.h>
#include <Texture.h>


#include "OBB.h"
#include "GameEntity.h"


GameEntity::GameEntity() {
}

GameEntity::GameEntity(aie::Texture * tex) : SpriteNode(tex) {
	collider = std::unique_ptr<OBB>(new OBB((float)tex->getWidth(), (float)tex->getHeight()));
	collider->debug(true);
	collider->setParent(this);
}


GameEntity::~GameEntity() {
}

void GameEntity::update(float dt) {
	SpriteNode::update(dt);
	collider->updatePointsByMatrix((float*)getTransform());
}

void GameEntity::render(aie::Renderer2D * renderer) {
	SpriteNode::render(renderer);
	collider->render(renderer);
}
