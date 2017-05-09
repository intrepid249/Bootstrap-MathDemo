#include "MathDemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Renderer2D.h"
#include "GameEntity.h"
#include "Node.h"

#include <Utility.h>
#include "OBB.h"
#include "settings.h"

#include "Tank.h"

#include <GLFW\glfw3.h>
#include <ResourceManager.h>

MathDemoApp::MathDemoApp() {

}

MathDemoApp::~MathDemoApp() {

}

void MathDemoApp::initControlLayouts() {
	// Control scheme for the tank
	controlLayouts[TANK_CONTROLS][FORWARD] = aie::INPUT_KEY_W;
	controlLayouts[TANK_CONTROLS][BACKWARD] = aie::INPUT_KEY_S;
	controlLayouts[TANK_CONTROLS][LEFT] = aie::INPUT_KEY_A;
	controlLayouts[TANK_CONTROLS][RIGHT] = aie::INPUT_KEY_D;
	controlLayouts[TANK_CONTROLS][SHOOT] = aie::INPUT_MOUSE_BUTTON_LEFT;
}

bool MathDemoApp::startup() {
	// Initialise the renderer
	m_renderer = std::unique_ptr<aie::Renderer2D>(new aie::Renderer2D());
	// Initialise the font
	m_font = ResourceManager::loadUniqueResource<aie::Font>("./font/consolas.ttf", 32);

	// Initialise the texture resources
	m_textures[TANK_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/tankBlue.png");
	m_textures[TANK_TURRET_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/barrelBlue.png");
	m_textures[TANK_BULLET_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/bullet.png");
	m_textures[RETICLE_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/Reticle.png");

	// Initialise the control schemes
	initControlLayouts();

	// Make a tank for the player to drive around in
	tank = std::unique_ptr<Tank>(new Tank(m_textures[TANK_TEX].get(), m_textures[TANK_TURRET_TEX].get(), m_textures[TANK_BULLET_TEX].get()));
	tank->translate(Vector2<float>(300, 300));
	// Give the user control so that we can drive around
	tank->setUserControlled(true);
	// Initialise the camera to the tank's position
	tank->setCamera(&m_cameraPos);
	// Set the control scheme for the tank
	tank->setControls(controlLayouts[TANK_CONTROLS]);
	m_nodes.push_back(tank.get());

	// Make a custom cursor reticle
	m_reticle = std::unique_ptr<SpriteNode>(new SpriteNode(m_textures[RETICLE_TEX].get()));

	worldOrigin = new Node();
	m_nodes.push_back(worldOrigin);

	return true;
}

void MathDemoApp::shutdown() {
	delete worldOrigin;
}

void MathDemoApp::update(float deltaTime) {

	// Hide the default cursor
	setShowCursor(false);

	aie::Input* input = aie::Input::getInstance();

	// Show the custom reticle image at the cursor position
	Vector2<int> mousePos;
	input->getMouseXY(&mousePos.x, &mousePos.y);
	m_reticle->getTransform().setTranslation((float)mousePos.x + m_cameraPos.x, (float)mousePos.y + m_cameraPos.y);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	//Update the list of world objects
	for (size_t i = 0; i < m_nodes.size(); ++i)
		m_nodes[i]->update(deltaTime);
}

void MathDemoApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_renderer->begin();

	// draw your stuff here!
	for (size_t i = 0; i < m_nodes.size(); ++i)
		m_nodes[i]->render(m_renderer.get());

#if 0
	//Code for testing collision functions
	if (tank->getCollider()->contains(m_mousePos))
		m_renderer->drawCircle(m_mousePos.x, m_mousePos.y, 3);
#endif

	m_reticle->render(m_renderer.get());
	m_renderer->drawText(m_font.get(), "Origin", 0, 0);

	// done drawing sprites
	m_renderer->end();
}
