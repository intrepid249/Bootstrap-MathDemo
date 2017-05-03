#pragma once
#include "Vehicle.h"
#include <memory>

class Tank : public Vehicle {
public:
	Tank();
	Tank(aie::Texture *baseTex, aie::Texture *turretTex);
	virtual ~Tank();

	virtual void update(float dt);
	virtual void render(aie::Renderer2D *renderer);
protected:
	std::unique_ptr<GameEntity> m_turret;
};

