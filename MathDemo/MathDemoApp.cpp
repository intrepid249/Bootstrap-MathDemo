#include "MathDemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Renderer2D.h"
#include "SpriteNode.h"
#include "Node.h"

#include <ResourceManager.h>

MathDemoApp::MathDemoApp() {

}

MathDemoApp::~MathDemoApp() {

}

bool MathDemoApp::startup() {
	m_renderer = std::unique_ptr<aie::Renderer2D>(new aie::Renderer2D());
	m_font = ResourceManager::loadUniqueResource<aie::Font>("./font/consolas.ttf", 32);

	m_textures[TANK_TEX] = ResourceManager::loadSharedResource<aie::Texture>("./textures/tankBlue.png");

	tank = std::unique_ptr<SpriteNode>(new SpriteNode(m_textures[TANK_TEX].get()));
	tank->translate(Vector2(300, 300));
	tank->debug(true);
	m_nodes.push_back(std::move(tank));

	return true;
}

void MathDemoApp::shutdown() {
}

void MathDemoApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void MathDemoApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_renderer->begin();

	// draw your stuff here!
	for (size_t i = 0; i < m_nodes.size(); ++i)
		m_nodes[i]->render(m_renderer.get());
	
	// output some text, uses the last used colour
	m_renderer->drawText(m_font.get(), "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_renderer->end();
}