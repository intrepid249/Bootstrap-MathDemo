#pragma once
#include "Nodes/SpriteNode.h"
#include <memory>
class OBB;
namespace aie {
	class Texture;
}

/** An object on-screen with a sprite image and an Oriented Bounding Box for collision
* @author Jack McCall*/
class GameEntity : public SpriteNode {
public:
	GameEntity();
	GameEntity(aie::Texture *tex);
	virtual ~GameEntity();

	/**Override the parent's update function
	* @see MathDemo::Node#update(float)*/
	virtual void update(float dt);
	/**Override the parent's render function
	* @see MathDemo::Node#render(aie::Renderer2D)*/
	virtual void render(aie::Renderer2D *renderer);

	/*Set the size of the Game Object*/
	void setSize(const Vector2<float> &size);
	/*Get the size of the Game Object*/
	Vector2<float>& getSize();

	/** Get a pointer to the collider box*/
	OBB* getCollider();

	/** Get a pointer to the particle texture*/
	virtual aie::Texture* getParticleType();

protected:
	aie::Texture *m_particleType;
	std::unique_ptr<OBB> m_collider;	// The object's Oriented Bounding Box
};