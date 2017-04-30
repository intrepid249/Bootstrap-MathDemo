#pragma once
class memory;
class AABB;
#include "SpriteNode.h"

class GameEntity : public SpriteNode {
public:
	GameEntity();
	GameEntity(aie::Texture *tex);
	~GameEntity();

	virtual void update(float dt);
	virtual void render(aie::Renderer2D *renderer);

protected:
	std::unique_ptr<AABB> collider;
};