#pragma once
#include <memory>
class OBB;
#include "SpriteNode.h"

class GameEntity : public SpriteNode {
public:
	GameEntity();
	GameEntity(aie::Texture *tex);
	~GameEntity();

	virtual void update(float dt);
	virtual void render(aie::Renderer2D *renderer);

protected:
	std::unique_ptr<OBB> collider;
};