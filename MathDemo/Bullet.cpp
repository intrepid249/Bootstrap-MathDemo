#include "Bullet.h"
#include "settings.h"
#include <Utility.h>

Bullet::Bullet() {
}

Bullet::Bullet(aie::Texture * tex) : GameEntity(tex) {
	m_lifetime = BULLET_LIFETIME;
}


Bullet::~Bullet() {
}

void Bullet::update(float dt) {
	// Move in it's direction
	Vector2<float> velocity = Vector2<float>(cosf(degToRad(getLocRot())) * BULLET_SPEED, sinf(degToRad(getLocRot())) * BULLET_SPEED);
	translate(velocity * dt);

	m_lifetime -= dt;
	if (m_lifetime <= 0)
		m_isDrawn = false;
}
