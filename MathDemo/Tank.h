#pragma once
#include "Vehicle.h"
#include "Bullet.h"
#include <memory>

class Tank : public Vehicle {
public:
	Tank();
	Tank(aie::Texture *baseTex, aie::Texture *turretTex, aie::Texture *bulletTex);
	virtual ~Tank();

	/** Overload the parent's update function*/
	virtual void update(float dt);
	/** Overload the parent's update controls function*/
	virtual void updateControls(aie::Input *input);
	/** Overload the parent's render function*/
	virtual void render(aie::Renderer2D *renderer);

	/** Gets a list of the bullet pointers*/
	virtual std::vector<GameEntity*> getBullets();
protected:
	std::unique_ptr<GameEntity> m_turret;
	std::unique_ptr<Node> m_barrel;
	aie::Texture *m_bulletTex;

	/// Some stuff to handle shooting
	/** This will loop the timer that resets the flag when we are able to
	shoot a bullet*/
	virtual void updateShooting(float dt);
	/** This will create a bullet*/
	virtual void shoot();

	std::vector<std::unique_ptr<Bullet>> m_bullets;
	bool m_isShooting, m_canShoot;
	float m_shootTimer;
};

