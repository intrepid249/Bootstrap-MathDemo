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
	virtual void renderStaticRotation(aie::Renderer2D *renderer);

	OBB* getCollider();

	void setStaticRotation(float angle);
	float getStaticRotation();

protected:
	std::unique_ptr<OBB> m_collider;
	float m_staticRotation = 0;
};