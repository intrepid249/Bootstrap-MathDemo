#include "Entities/Vehicles/Vehicle.h"
#include <Texture.h>
#include "settings.h"
#include <Utility.h>

#include <Renderer2D.h>

#include <iostream>


Vehicle::Vehicle() {
	m_moveBW = m_moveFW = m_turnL = m_turnR = false;
	m_userControlled = false;
}

Vehicle::Vehicle(aie::Texture * tex) :  GameEntity(tex) {
	m_moveBW = m_moveFW = m_turnL = m_turnR = false;
	m_userControlled = false;
}


Vehicle::~Vehicle() {
}

/*
Store the control codes for the vehicle's movement/behaviour
*/
void Vehicle::setControls(std::map<eControlID, aie::EInputCodes> controlScheme) {
	m_controls = controlScheme;
}

/*
This updates the control flags to tell the object to move or stop moving
when we press or release a key
*/
void Vehicle::updateControls(aie::Input * input) {
	if (input->isKeyDown(m_controls[FORWARD]))
		m_moveFW = true;
	if (input->isKeyDown(m_controls[BACKWARD]))
		m_moveBW = true;
	if (input->isKeyDown(m_controls[LEFT]))
		m_turnL = true;
	if (input->isKeyDown(m_controls[RIGHT]))
		m_turnR = true;

	if (input->isKeyUp(m_controls[FORWARD]))
		m_moveFW = false;
	if (input->isKeyUp(m_controls[BACKWARD]))
		m_moveBW = false;
	if (input->isKeyUp(m_controls[LEFT]))
		m_turnL = false;
	if (input->isKeyUp(m_controls[RIGHT]))
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

		// Translate the camera position
		Vector2<float> camPos = getTransform().getTranslation();
		camPos.x -= SCREENWIDTH / 2;
		camPos.y -= SCREENHEIGHT / 2;

		*m_cameraPos = camPos;


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
