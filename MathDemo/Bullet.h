#pragma once
#include "GameEntity.h"
#include <Texture.h>

class Bullet : public GameEntity {
public:
	Bullet();
	Bullet(aie::Texture *tex);
	~Bullet();

	virtual void update(float dt);

	void setMoveSpeed(float speed);
	void setLifetime(float lifespan);

protected:
	float m_lifetime;
	float m_moveSpeed;
};

