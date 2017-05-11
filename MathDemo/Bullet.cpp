#include "Bullet.h"
#include "settings.h"
#include <Utility.h>

Bullet::Bullet() {
}

Bullet::Bullet(aie::Texture * tex) : GameEntity(tex) {
	m_lifetime = m_lifetime;
}


Bullet::~Bullet() {
}

void Bullet::update(float dt) {
	GameEntity::update(dt);
	// Move in it's direction
	Vector2<float> velocity = Vector2<float>(cosf(degToRad(getLocRot())) * m_moveSpeed, sinf(degToRad(getLocRot())) * m_moveSpeed);
	translate(velocity * dt);

	m_lifetime -= dt;
	if (m_lifetime <= 0)
		m_isDrawn = false;
}

void Bullet::setMoveSpeed(float speed) {
	m_moveSpeed = speed;
}

void Bullet::setLifetime(float lifespan) {
	m_lifetime = lifespan;
}
