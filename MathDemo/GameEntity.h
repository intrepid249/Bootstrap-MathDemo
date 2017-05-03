#pragma once
#include <memory>
class OBB;
#include "SpriteNode.h"

class GameEntity : public SpriteNode {
public:
	GameEntity();
	GameEntity(aie::Texture *tex);
	virtual ~GameEntity();

	virtual void update(float dt);
	virtual void render(aie::Renderer2D *renderer);

	OBB* getCollider();

protected:
	std::unique_ptr<OBB> m_collider;
};