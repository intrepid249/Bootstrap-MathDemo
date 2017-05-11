#pragma once
#include <memory>
class OBB;
#include "SpriteNode.h"

class GameEntity : public SpriteNode {
public:
	GameEntity();
	GameEntity(aie::Texture *tex);
	virtual ~GameEntity();

	/**Overload the parent's update function*/
	virtual void update(float dt);
	/**Overload the parent's render function*/
	virtual void render(aie::Renderer2D *renderer);
	/**Calculate collision against a collection of objects*/
	//virtual bool checkCollision(std::vector<Node*> objects);

	// Get a pointer to the collider box
	OBB* getCollider();

protected:
	std::unique_ptr<OBB> m_collider;
};