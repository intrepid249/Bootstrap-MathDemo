#include "Vehicle.h"
#include <Texture.h>
#include "settings.h"
#include <Utility.h>

#include <Renderer2D.h>

#include <iostream>


Vehicle::Vehicle() {
	m_moveBW = m_moveFW = m_turnL = m_turnR = false;
}

Vehicle::Vehicle(aie::Texture * tex) : GameEntity(tex) {
	m_moveBW = m_moveFW = m_turnL = m_turnR = false;
}


Vehicle::~Vehicle() {
}

/*
store the control codes for the vehicle's movement/behaviour
*/
void Vehicle::setControls(aie::EInputCodes fwKey, aie::EInputCodes bwKey, aie::EInputCodes lKey, aie::EInputCodes rKey) {
	m_fwKey = fwKey, m_bwKey = bwKey, m_lKey = lKey, m_rKey = rKey;
}

/*
this updates the control flags to tell the object to move or stop moving
when we press or release a key
*/
void Vehicle::updateControls(aie::Input * input) {
	if (input->isKeyDown(m_fwKey))
		m_moveFW = true;
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

void Vehicle::update(float dt) {
	GameEntity::update(dt);

	if (m_userControlled) {
		aie::Input *input = aie::Input::getInstance();
		updateControls(input);

		///Movement controls
		// update the position so we move along the 'heading' vector
		float rot = degToRad(getLocRot());

		if (m_moveFW) {
			m_moveSpeed = Vector2<float>(cosf(rot) * TANK_MOVESPEED, sinf(rot) * TANK_MOVESPEED);
		} else if (m_moveBW) {
			m_moveSpeed = Vector2<float>(-cosf(rot) * TANK_MOVESPEED, -sinf(rot) * TANK_MOVESPEED);
		} else
			m_moveSpeed = Vector2<float>(0, 0);

		///Rotation controls
		// update the rotation to turn our heading vector
		if (m_turnL)
			m_turnSpeed = TANK_TURNSPEED;
		else if (m_turnR)
			m_turnSpeed = -TANK_TURNSPEED;
		else
			m_turnSpeed = 0;

		Vector2<float> cPos = getTransform().getTranslation();
		cPos.x -= SCREENWIDTH / 2;
		cPos.y -= SCREENHEIGHT / 2;

		*m_cameraPos = cPos;


		// Perform calculations in the order scale * rotation * translation
		rotate(m_turnSpeed * dt);
		translate(m_moveSpeed * dt);
	}
}

void Vehicle::render(aie::Renderer2D * renderer) {
	GameEntity::render(renderer);

	if (m_userControlled)
		renderer->setCameraPos(m_cameraPos->x, m_cameraPos->y);
}

void Vehicle::faceAtPoint(Vector2<float> & point, GameEntity *obj) {
	Vector2<float> target = point - obj->calculateGlobalTransform().getTranslation();
	float radians = atan2f(target.y, target.x);
	obj->getTransform().setRotateZ(radians);
}

void Vehicle::setCamera(Vector2<float> * camPos) {
	m_cameraPos = camPos;
}

void Vehicle::setUserControlled(bool flag) {
	m_userControlled = flag;
}

bool Vehicle::isUserControlled() {
	return m_userControlled;
}
