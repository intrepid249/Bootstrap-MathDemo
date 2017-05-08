#include "Tank.h"
#include <Renderer2D.h>
#include <Vector2.h>


Tank::Tank() {}

Tank::Tank(aie::Texture * baseTex, aie::Texture * turretTex) : Vehicle(baseTex) {
	m_turret = std::unique_ptr<GameEntity>(new GameEntity(turretTex));
	m_turret->setOrigin(Vector2<float>(0.0f, 0.5f));
	m_turret->setParent(this);
}

Tank::~Tank() {}

void Tank::update(float dt) {
	Vehicle::update(dt);

	aie::Input *input = aie::Input::getInstance();

	if (m_userControlled) {
		// Calculate the mouse position on the screen
		int mouseX, mouseY;
		input->getMouseXY(&mouseX, &mouseY);
		Vector2<float> mousePos = Vector2<float>((float)mouseX, (float)mouseY);

		mousePos += *m_cameraPos;
		mousePos -= getTransform().getTranslation();

		///Turret
		// Rotate the turret to face the mouse
		m_turret->setStaticRotation(atan2f(mousePos.y, mousePos.x));
	}
}

void Tank::render(aie::Renderer2D * renderer) {
	Vehicle::render(renderer);
	m_turret->renderStaticRotation(renderer);
}
