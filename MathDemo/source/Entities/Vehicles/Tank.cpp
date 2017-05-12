#include "Entities/Vehicles/Tank.h"
#include <Renderer2D.h>
#include <Vector2.h>
#include <Utility.h>
#include "Colliders/OBB.h"
#include "Particles/ParticleGenerator.h"
#include <Texture.h>
#include <ResourceManager\ResourceManager.h>

#include <iostream>

Tank::Tank() {
	m_isShootingMainGun = false; m_canShootMainGun = true;
	m_mainGunTimer = 0;
	m_isShootingMachinegun = false; m_canShootMachinegun = true;
	m_machinegunTimer = 0;
}

Tank::Tank(aie::Texture * baseTex, aie::Texture * turretTex, aie::Texture * bulletTex, aie::Texture * shellTex) : Vehicle(baseTex) {
	m_isShootingMainGun = false; m_canShootMainGun = true;
	m_mainGunTimer = 0;
	m_isShootingMachinegun = false; m_canShootMachinegun = true;
	m_machinegunTimer = 0;

	// Initialise the turret
	m_turret = std::unique_ptr<GameEntity>(new GameEntity(turretTex));
	m_turret->setOrigin(Vector2<float>(0.2f, 0.5f));
	m_turret->setParent(this);

	// Set the node handle for where we create tank shells
	m_barrel = std::unique_ptr<Node>(new Node());
	m_barrel->translate(Vector2<float>(m_turret->getSize().x, 0));
	m_barrel->setParent(m_turret.get());

	m_machinegunLeft = std::unique_ptr<Node>(new Node());
	m_machinegunLeft->translate(Vector2<float>(m_turret->getSize().x / 2, m_turret->getSize().y / 2 - 5));
	m_machinegunLeft->setParent(m_turret.get());

	m_machinegunRight = std::unique_ptr<Node>(new Node());
	m_machinegunRight->translate(Vector2<float>(m_turret->getSize().x / 2, -m_turret->getSize().y / 2 + 5));
	m_machinegunRight->setParent(m_turret.get());

	// Store a pointer to the bullet texture
	m_bulletTex = bulletTex;
	m_shellTex = shellTex;
}

Tank::~Tank() {
}

void Tank::update(float dt) {
	Vehicle::update(dt);
	m_turret->update(dt);

	// Get an instance of the external input devices
	aie::Input *input = aie::Input::getInstance();

	updateControls(input);

	if (m_userControlled) {
		/// Shooting events
		updateMainGun(dt);
		if (m_isShootingMainGun && m_canShootMainGun)
			shootMainGun();
		updateMachinegun(dt);
		if (m_isShootingMachinegun && m_canShootMachinegun)
			shootMachinegun();

		for (size_t i = 0; i < m_bullets.size(); ++i)
			m_bullets[i]->update(dt);

		for (size_t i = 0; i < m_particleGenerators.size(); ++i)
			m_particleGenerators[i]->update(dt);

		// Calculate the mouse position on the screen
		int mouseX, mouseY;
		input->getMouseXY(&mouseX, &mouseY);
		Vector2<float> mousePos = Vector2<float>((float)mouseX, (float)mouseY);

		// make the mouse coordinates relative to the camera coordinate system
		mousePos += *m_cameraPos;
		mousePos -= getTransform().getTranslation();

		///Turret
		// Rotate the turret to face the mouse -> separate the turret's rotation from the parent's rotation matrix
		m_turret->setRotate(atan2f(mousePos.y, mousePos.x) - getLocRot());

		// Rotate the barrel's bullet spawning node
		float rad = degToRad(m_turret->getTransform().getRotationZ());
		m_barrel->translate(Vector2<float>(-m_barrel->getLocPos().x, 0.0f)); // translate it back to the origin of rotation
		m_barrel->setRotate(rad); // rotate around the offset
		m_barrel->translate(Vector2<float>(m_turret->getSize().x, 0.0f)); // and put it back where it should be


		///Machine guns
		// left gun
		m_machinegunLeft->translate(Vector2<float>(-m_turret->getSize().x / 2, 0.0f)); // translate it back to the origin of rotation
		m_machinegunLeft->setRotate(rad); // rotate around the offset
		m_machinegunLeft->translate(Vector2<float>(m_turret->getSize().x / 2, 0.0f)); // and put it back where it should be
		// right gun
		m_machinegunRight->translate(Vector2<float>(-m_turret->getSize().x / 2, 0.0f)); // translate it back to the origin of rotation
		m_machinegunRight->setRotate(rad); // rotate around the offset
		m_machinegunRight->translate(Vector2<float>(m_turret->getSize().x / 2, 0.0f)); // and put it back where it should be

		doCleanup();
	}
}

void Tank::updateControls(aie::Input * input) {
	Vehicle::updateControls(input);
	
	// Update shooting control flags
	if (input->isMouseButtonDown(m_controls[SHOOT]))
		m_isShootingMainGun = true;
	if (input->isMouseButtonUp(m_controls[SHOOT]))
		m_isShootingMainGun = false;
	if (input->isMouseButtonDown(m_controls[SECONDARYFIRE]))
		m_isShootingMachinegun = true;
	if (input->isMouseButtonUp(m_controls[SECONDARYFIRE]))
		m_isShootingMachinegun = false;
}

void Tank::render(aie::Renderer2D * renderer) {
	Vehicle::render(renderer);
	m_turret->render(renderer);
	m_barrel->render(renderer);
	m_machinegunLeft->render(renderer);
	m_machinegunRight->render(renderer);

	for (size_t i = 0; i < m_bullets.size(); ++i)
		m_bullets[i]->render(renderer);

	for (size_t i = 0; i < m_particleGenerators.size(); ++i)
		m_particleGenerators[i]->render(renderer);
}

bool Tank::checkCollision(std::vector<Node*> objects) {
	for (size_t i = 0; i < m_bullets.size(); ++i) {
		OBB* collider = m_bullets[i]->getCollider();
		for (size_t o = 0; o < objects.size(); ++o)
			if (collider->collides(*objects[o]->getCollider())) {
				std::unique_ptr<ParticleGenerator> pgen = std::unique_ptr<ParticleGenerator>(new ParticleGenerator(objects[o]->getTexture()));
				pgen->setLifetime(1.2);
				pgen->translate(m_bullets[i]->getTransform().getTranslation());
				pgen->createExplosion(3, 10, 5, 15);
				m_particleGenerators.push_back(std::move(pgen));
				m_bullets[i]->setDrawn(false);
				return true;
			}
	}
	return false;
}

std::vector<Bullet*> Tank::getBullets() {
	std::vector<Bullet*> temp;

	for (size_t i = 0; i < m_bullets.size(); ++i)
		temp.push_back(m_bullets[i].get());
	
	return temp;
}

void Tank::updateMainGun(float dt) {
	m_mainGunTimer += dt;

	if (m_mainGunTimer < TANK_CANNON_SHOTDELAY) return;
	// If we can shoot again
	m_mainGunTimer = 0;
	m_canShootMainGun = true;
}

void Tank::shootMainGun() {
	m_canShootMainGun = false;
	
	std::unique_ptr<Bullet> bullet = std::unique_ptr<Bullet>(new Bullet(m_shellTex));
	bullet->translate(m_barrel->calculateGlobalTransform().getTranslation());
	bullet->setRotate(m_barrel->calculateGlobalTransform().getRotationZ());
	bullet->setMoveSpeed(TANKSHELL_SPEED);
	bullet->setLifetime(TANKSHELL_LIFETIME);
	m_bullets.push_back(std::move(bullet));
}

void Tank::updateMachinegun(float dt) {
	m_machinegunTimer += dt;

	if (m_machinegunTimer < TANK_MACHINEGUN_SHOTDELAY) return;
	// If we can shoot again
	m_machinegunTimer = 0;
	m_canShootMachinegun = true;
}

void Tank::shootMachinegun() {
	m_canShootMachinegun = false;

	// Left gun's bullet
	std::unique_ptr<Bullet> bullet1 = std::unique_ptr<Bullet>(new Bullet(m_bulletTex));
	bullet1->translate(m_machinegunLeft->calculateGlobalTransform().getTranslation());
	bullet1->setRotate(m_machinegunLeft->calculateGlobalTransform().getRotationZ());
	bullet1->setMoveSpeed(TANKBULLET_SPEED);
	bullet1->setLifetime(TANKBULLET_LIFETIME);
	m_bullets.push_back(std::move(bullet1));

	// Right gun's bullet
	std::unique_ptr<Bullet> bullet2 = std::unique_ptr<Bullet>(new Bullet(m_bulletTex));
	bullet2->translate(m_machinegunRight->calculateGlobalTransform().getTranslation());
	bullet2->setRotate(m_machinegunRight->calculateGlobalTransform().getRotationZ());
	bullet2->setMoveSpeed(TANKBULLET_SPEED);
	bullet2->setLifetime(TANKBULLET_LIFETIME);
	m_bullets.push_back(std::move(bullet2));
}

void Tank::doCleanup() {
	for (size_t i = 0; i < m_bullets.size(); ++i)
		if (!m_bullets[i]->isDrawn())
			m_bullets.erase(m_bullets.begin() + i);

	for (size_t i = 0; i < m_particleGenerators.size(); ++i)
		if (!m_particleGenerators[i]->isDrawn())
			m_particleGenerators.erase(m_particleGenerators.begin() + i);
}
