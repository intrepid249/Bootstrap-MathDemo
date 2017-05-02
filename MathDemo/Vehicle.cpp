#include "Vehicle.h"
#include <Texture.h>
#include "settings.h"

#include <iostream>


Vehicle::Vehicle() {
	m_moveBW = m_moveFW = m_turnL = m_turnR = false;
}

Vehicle::Vehicle(aie::Texture * tex) : GameEntity(tex) {
	m_moveBW = m_moveFW = m_turnL = m_turnR = false;
}


Vehicle::~Vehicle() {
}

void Vehicle::setControls(aie::EInputCodes fwKey, aie::EInputCodes bwKey, aie::EInputCodes lKey, aie::EInputCodes rKey) {
	m_fwKey = fwKey, m_bwKey = bwKey, m_lKey = lKey, m_rKey = rKey;
}

void Vehicle::updateControls(aie::Input * input) {
	if (input->isKeyDown(m_fwKey))
		m_moveFW = true, std::cout<<"MoveFW\n";
	if (input->isKeyDown(m_bwKey))
		m_moveBW = true;
	if (input->isKeyDown(m_lKey))
		m_turnL = true;
	if (input->isKeyDown(m_rKey))
		m_turnR = true;

	if (input->isKeyUp(m_fwKey))
		m_moveFW = false;
	if (input->isKeyUp(m_bwKey))
		m_moveBW = false;
	if (input->isKeyUp(m_lKey))
		m_turnL = false;
	if (input->isKeyUp(m_rKey))
		m_turnR = false;
}

void Vehicle::updateToFaceMouse(Vector2 & mousePos) {
	Vector2 target = mousePos - getLocPos();
	float radians = atan2f(target.y, target.x);
	getTransform().setRotateZ(radians);
}

void Vehicle::update(float dt) {
	GameEntity::update(dt);

	float rot = getTransform().getRotationZ();
	if (m_moveFW)
		setMoveSpeed(Vector2(cosf(rot) * TANK_MOVESPEED, sinf(rot) * TANK_MOVESPEED));
	else if (m_moveBW)
		setMoveSpeed(Vector2(-cosf(rot) * TANK_MOVESPEED, -sinf(rot) * TANK_MOVESPEED));
	else
		setMoveSpeed(Vector2(0, 0));

	translate(m_moveSpeed);
}

void Vehicle::render(aie::Renderer2D * renderer) {
	GameEntity::render(renderer);
}

void Vehicle::setMoveSpeed(const Vector2 val) {
	m_moveSpeed = val;
}
