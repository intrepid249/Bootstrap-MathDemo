#pragma once
#include "GameEntity.h"
#include <Texture.h>

/** Object with a movement speed in its forward direction and a set lifetime
* @author Jack McCall*/
class Bullet : public GameEntity {
public:
	Bullet();
	/** Create a new bullet object
	* @param tex - pointer to the loaded texture*/
	Bullet(aie::Texture *tex);
	~Bullet();

	/** Overload the parent's update function
	* @see MathDemo::Node#update(float)*/
	virtual void update(float dt);
	
	/** Sets the movement speed of the bullet*/
	void setMoveSpeed(float speed);
	/** Sets the amount of time (in seconds) the bullet will stay alive*/
	void setLifetime(float lifespan);

protected:
	float m_lifetime;
	float m_moveSpeed;
};

