#include "MathDemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Renderer2D.h"
#include "GameEntity.h"
#include "Node.h"
#include "Vehicle.h"
#include <Utility.h>
#include "OBB.h"

#include <ResourceManager.h>

MathDemoApp::MathDemoApp() {

}

MathDemoApp::~MathDemoApp() {

}

bool MathDemoApp::startup() {
	m_renderer = std::unique_ptr<aie::Renderer2D>(new aie::Renderer2D());
	m_font = ResourceManager::loadUniqueResource<aie::Font>("./font/consolas.ttf", 32);

	m_textures[TANK_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/tankBlue.png");

	tank = std::unique_ptr<GameEntity>(new GameEntity(m_textures[TANK_TEX].get()));
	tank->translate(Vector2(300, 300));
	tank->debug(true);
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

	// Get the mouse position on the screen
	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);
	m_mousePos = Vector2(mouseX, mouseY);


	tank->rotate(degToRad(.5f));

	float x = rand() % 10 * 0.1f, y = rand() % 4 * 0.1f;
	tank->translate(Vector2(x, y));

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

	if (tank->getCollider()->contains(m_mousePos))
		m_renderer->drawCircle(m_mousePos.x, m_mousePos.y, 3);

	m_renderer->drawText(m_font.get(), "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_renderer->end();
}