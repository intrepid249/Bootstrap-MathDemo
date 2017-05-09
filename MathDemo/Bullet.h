#pragma once
#include "GameEntity.h"
#include <Texture.h>

class Bullet : public GameEntity {
public:
	Bullet();
	Bullet(aie::Texture *tex);
	~Bullet();

	virtual void update(float dt);

protected:
	float m_lifetime;
};

