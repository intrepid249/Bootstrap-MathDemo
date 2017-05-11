#pragma once
#include "Vehicle.h"
#include "Bullet.h"
#include <memory>

class Tank : public Vehicle {
public:
	Tank();
	Tank(aie::Texture *baseTex, aie::Texture *turretTex, aie::Texture *bulletTex, aie::Texture *shellTex);
	virtual ~Tank();

	/** Overload the parent's update function*/
	virtual void update(float dt);
	/** Overload the parent's update controls function*/
	virtual void updateControls(aie::Input *input);
	/** Overload the parent's render function*/
	virtual void render(aie::Renderer2D *renderer);
	/**Calculate collision against a collection of objects*/
	virtual bool checkCollision(std::vector<Node*> objects);

	/** Gets a list of the bullet pointers*/
	virtual std::vector<Bullet*> getBullets();
protected:
	std::unique_ptr<GameEntity> m_turret;
	std::unique_ptr<Node> m_barrel;
	std::unique_ptr<Node> m_machinegunLeft, m_machinegunRight;
	aie::Texture *m_bulletTex, *m_shellTex;

	/// Some stuff to handle shooting
	/** This will loop the timer that resets the flag when we are able to
	shoot a bullet*/
	virtual void updateMainGun(float dt);
	/** This will create a bullet*/
	virtual void shootMainGun();
	/** This will loop the timer that resets the flag when we are able to
	shoot a bullet*/
	virtual void updateMachinegun(float dt);
	/** This will create a bullet*/
	virtual void shootMachinegun();
	/** Clean up the memory for all the 'dead' bullets*/
	virtual void cleanupBullets();

	std::vector<std::unique_ptr<Bullet>> m_bullets;
	bool m_isShootingMainGun, m_canShootMainGun, m_isShootingMachinegun, m_canShootMachinegun;
	float m_mainGunTimer, m_machinegunTimer;
};

