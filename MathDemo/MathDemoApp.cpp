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

#include <ResourceManager.h>

MathDemoApp::MathDemoApp() {

}

MathDemoApp::~MathDemoApp() {

}

bool MathDemoApp::startup() {
	m_renderer = std::unique_ptr<aie::Renderer2D>(new aie::Renderer2D());
	m_font = ResourceManager::loadUniqueResource<aie::Font>("./font/consolas.ttf", 32);

	m_textures[TANK_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/tankBlue.png");
	m_textures[TANK_TURRET_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/barrelBlue.png");

	tank = std::unique_ptr<Tank>(new Tank(m_textures[TANK_TEX].get(), m_textures[TANK_TURRET_TEX].get()));
	tank->translate(Vector2<float>(300, 300));
	tank->setUserControlled(true);
	tank->setCamera(&m_cameraPos);
	tank->setControls(aie::INPUT_KEY_W, aie::INPUT_KEY_S, aie::INPUT_KEY_A, aie::INPUT_KEY_D);
	m_nodes.push_back(tank.get());

	return true;
}

void MathDemoApp::shutdown() {
}

void MathDemoApp::update(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();
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

	m_renderer->drawText(m_font.get(), "Origin", 0, 0);

	// done drawing sprites
	m_renderer->end();
}