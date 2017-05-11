#pragma once
#include "GameEntity.h"
#include <Texture.h>

class Bullet : public GameEntity {
public:
	Bullet();
	/** Create a new bullet object
	* @param tex - pointer to the loaded texture*/
	Bullet(aie::Texture *tex);
	~Bullet();

	/** Overload the parent's update function
	* @param dt - deltaTime (amount of time since last frame)*/
	virtual void update(float dt);

	void setMoveSpeed(float speed);
	void setLifetime(float lifespan);

protected:
	float m_lifetime;
	float m_moveSpeed;
};

