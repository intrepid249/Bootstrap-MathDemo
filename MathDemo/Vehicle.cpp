#include "Vehicle.h"
#include <Texture.h>


Vehicle::Vehicle() {
	m_moveBW = m_moveFW = m_turnL = m_turnR = false;
}

Vehicle::Vehicle(aie::Texture * tex) {

}


Vehicle::~Vehicle() {
}

void Vehicle::setControls(aie::EInputCodes fwKey, aie::EInputCodes bwKey, aie::EInputCodes lKey, aie::EInputCodes rKey) {
	m_fwKey = fwKey, m_bwKey = bwKey, m_lKey = lKey, m_rKey = rKey;
}

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

void Vehicle::updateToFaceMouse(Vector2 & mousePos) {

}

void Vehicle::update(float dt) {}

void Vehicle::render(aie::Renderer2D * renderer) {}
