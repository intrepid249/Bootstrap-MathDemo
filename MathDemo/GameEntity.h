#pragma once
#include <memory>
class OBB;
#include "SpriteNode.h"

/** An object on-screen with a sprite image and an Oriented Bounding Box for collision
* @author Jack McCall*/
class GameEntity : public SpriteNode {
public:
	GameEntity();
	GameEntity(aie::Texture *tex);
	virtual ~GameEntity();

	/**Overload the parent's update function
	* @see MathDemo::Node#update(float)*/
	virtual void update(float dt);
	/**Overload the parent's render function
	* @see MathDemo::Node#render(aie::Renderer2D)*/
	virtual void render(aie::Renderer2D *renderer);
#if 0
	/**Calculate collision against a collection of objects*/
	virtual bool checkCollision(std::vector<Node*> objects);
#endif

	/** Get a pointer to the collider box*/
	OBB* getCollider();

protected:
	std::unique_ptr<OBB> m_collider;	// The object's Oriented Bounding Box
};