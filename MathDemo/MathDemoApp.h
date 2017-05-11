#pragma once
#include "Application.h"
#include <vector>
#include <map>
#include <memory>
#include <Texture.h>
#include <Vector2.h>
#include "settings.h"
#include <Input.h>
#include "SpriteNode.h"

#include "GameEntity.h"

namespace aie {
	class Font;
	class Renderer2D;
};

class Node;
class GameEntity;
class Tank;

class MathDemoApp : public aie::Application {
public:
	MathDemoApp();
	virtual ~MathDemoApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void checkCollisions();

private:
	/**Initialise the control schemes*/
	void initControlLayouts();

protected:
	enum eTexID { TANK_TEX, TANK_TURRET_TEX, TANK_BULLET_TEX, TANK_SHELL_TEX, LARGE_ROCK_TEX, RETICLE_TEX };
	enum eControlSchemes { TANK_CONTROLS = 0xCAFE, PLAYER_CONTROLS }; // some code we can 'sink our teeth' into

	std::map<eTexID, std::shared_ptr<aie::Texture>> m_textures;

	std::map<eControlSchemes, std::map<eControlID, aie::EInputCodes>> controlLayouts;

	std::unique_ptr<SpriteNode> m_reticle;
	std::unique_ptr<Tank>	tank;	// Used to test movement
	std::vector<Node*>	m_nodes;	// The list of all the Nodes in the worldspace

	Node* worldOrigin;	// Used to keep track of the world's origin coordinate

	std::unique_ptr<aie::Renderer2D>	m_renderer;
	std::unique_ptr<aie::Font>			m_font;


	std::vector<std::unique_ptr<GameEntity>> m_rocks;

	Vector2<float> m_cameraPos;
	//OBB m_northBounds, m_southBounds, m_eastBounds, m_westBounds;
};