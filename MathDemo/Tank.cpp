#include "Tank.h"
#include <Renderer2D.h>
#include <Vector2.h>
#include <Utility.h>

#include <iostream>

Tank::Tank() {
	m_isShooting = false; m_canShoot = true;
	m_shootTimer = 0;
}

Tank::Tank(aie::Texture * baseTex, aie::Texture * turretTex, aie::Texture * bulletTex) : Vehicle(baseTex) {
	m_isShooting = false; m_canShoot = true;
	m_shootTimer = 0;

	// Initialise the turret
	m_turret = std::unique_ptr<GameEntity>(new GameEntity(turretTex));
	m_turret->setOrigin(Vector2<float>(0.0f, 0.5f));
	m_turret->setParent(this);

	// Set the node handle for where we create bullets
	m_barrel = std::unique_ptr<Node>(new Node());
	m_barrel->translate(Vector2<float>(m_turret->getSize().x, 0));
	m_barrel->setParent(m_turret.get());

	// Store a pointer to the bullet texture
	m_bulletTex = bulletTex;
}

Tank::~Tank() {
}

void Tank::update(float dt) {
	Vehicle::update(dt);

	// Get an instance of the external input devices
	aie::Input *input = aie::Input::getInstance();

	updateControls(input);

	if (m_userControlled) {
		/// Shooting events
		updateShooting(dt);
		if (m_isShooting && m_canShoot)
			shoot();

		for (size_t i = 0; i < m_bullets.size(); ++i)
			m_bullets[i]->update(dt);

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
		m_barrel->translate(Vector2<float>(-m_turret->getSize().x, 0.0f)); // translate it back to the origin of rotation
		m_barrel->setRotate(rad); // rotate around the offset
		m_barrel->translate(Vector2<float>(m_turret->getSize().x, 0.0f)); // and put it back where it should be
	}
}

void Tank::updateControls(aie::Input * input) {
	Vehicle::updateControls(input);
	
	if (input->isMouseButtonDown(m_controls[SHOOT]))
		m_isShooting = true;
	if (input->isMouseButtonUp(m_controls[SHOOT]))
		m_isShooting = false;
}

void Tank::render(aie::Renderer2D * renderer) {
	Vehicle::render(renderer);
	m_turret->render(renderer);
	m_barrel->render(renderer);

	for (size_t i = 0; i < m_bullets.size(); ++i)
		m_bullets[i]->render(renderer);
}

std::vector<GameEntity*> Tank::getBullets() {
	std::vector<GameEntity*> temp;

	for (size_t i = 0; i < m_bullets.size(); ++i)
		temp.push_back(m_bullets[i].get());
	
	return temp;
}

void Tank::updateShooting(float dt) {
	m_shootTimer += dt;

	if (m_shootTimer < TANK_SHOTDELAY) return;
	// If we can shoot again
	m_shootTimer = 0;
	m_canShoot = true;
}

void Tank::shoot() {
	m_canShoot = false;
	
	std::unique_ptr<Bullet> bullet = std::unique_ptr<Bullet>(new Bullet(m_bulletTex));
	bullet->translate(m_barrel->calculateGlobalTransform().getTranslation());
	bullet->setRotate(m_barrel->calculateGlobalTransform().getRotationZ());
	m_bullets.push_back(std::move(bullet));
	
}
