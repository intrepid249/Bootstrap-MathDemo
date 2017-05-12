#pragma once
#include "Entities/Vehicles/Vehicle.h"
#include "Entities/Bullet.h"
#include <memory>

class ParticleGenerator;

/** A specialised vehicle class that allows the user to shoot bullets and tank shells
* @author Jack McCall*/
class Tank : public Vehicle {
public:
	Tank();
	/** Create a new Tank object
	* @param baseTex - pointer to the loaded texture for the tank's chassis
	* @param turretTex - pointer to the loaded texture for the tank's turret
	* @param bulletTex - pointer to the loaded texture for the machinegun bullets
	* @param shellTex - pointer to the loaded texture for the main cannon shells*/
	Tank(aie::Texture *baseTex, aie::Texture *turretTex, aie::Texture *bulletTex, aie::Texture *shellTex);
	virtual ~Tank();

	/** Overload the parent's update function
	* @see MathDemo::Node#update(float)*/
	virtual void update(float dt);
	/** Overload the parent's update controls function
	* @see MathDemo::Vehicle#updateControls(aie::Input)*/
	virtual void updateControls(aie::Input *input);
	/** Overload the parent's render function
	* @see MathDemo::Node#render(aie::Renderer2D)*/
	virtual void render(aie::Renderer2D *renderer);
	/**Calculate collision against a collection of objects*/
	virtual bool checkCollision(std::vector<Node*> objects);

	/** Gets a list of the bullet pointers*/
	virtual std::vector<Bullet*> getBullets();
protected:
	
	std::unique_ptr<GameEntity> m_turret;	// The turret object that is a child of the tank
	std::unique_ptr<Node> m_barrel;			// The node handle to spawn tank shells from
	std::unique_ptr<Node> m_machinegunLeft, m_machinegunRight;	// The node handle to spawn machinegun bullets from
	aie::Texture *m_bulletTex, *m_shellTex;	// Pointer to the image held elsewhere in the program

	/// Some stuff to handle shooting
	/** This will loop the timer that resets the flag when we are able to
	shoot a tank shell
	* @param dt - deltaTime (amount of time since last frame)*/
	virtual void updateMainGun(float dt);
	/** This will create a bullet*/
	virtual void shootMainGun();
	/** This will loop the timer that resets the flag when we are able to
	shoot a bullet
	* @param dt - deltaTime (amount of time since last frame)*/
	virtual void updateMachinegun(float dt);
	/** This will create a bullet*/
	virtual void shootMachinegun();
	/** Clean up the memory for all the 'dead' bullets*/
	virtual void doCleanup();

	std::vector<std::unique_ptr<ParticleGenerator>> m_particleGenerators;
	std::vector<std::unique_ptr<Bullet>> m_bullets;	// A list of all the bullets we're shooting
	bool m_isShootingMainGun, m_canShootMainGun, m_isShootingMachinegun, m_canShootMachinegun;
	float m_mainGunTimer, m_machinegunTimer;
};

