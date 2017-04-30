#pragma once
#include "Application.h"
#include <vector>
#include <map>
#include <memory>
#include <Texture.h>

namespace aie {
	class Font;
	class Renderer2D;
};

class Node;
class GameEntity;

class MathDemoApp : public aie::Application {
public:
	MathDemoApp();
	virtual ~MathDemoApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	enum eTexID { TANK_TEX };

	std::map<eTexID, std::shared_ptr<aie::Texture>> m_textures;

	std::unique_ptr<GameEntity>	tank;
	std::vector<std::unique_ptr<Node>>	m_nodes;

	std::unique_ptr<aie::Renderer2D>	m_renderer;
	std::unique_ptr<aie::Font>			m_font;

	
};