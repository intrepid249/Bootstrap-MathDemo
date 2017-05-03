#pragma once
#include "Node.h"
namespace aie {
	class Texture;
}

class SpriteNode : public Node {
public:
	SpriteNode();
	SpriteNode(aie::Texture *m_tex);
	~SpriteNode();

	virtual void render(aie::Renderer2D *renderer);
	virtual void renderByMatrix(aie::Renderer2D * renderer, float * mat);

	void setSize(const Vector2 &size);
	Vector2& getSize();

	void setOrigin(const Vector2 &origin);
	Vector2& getOrigin();

protected:
	aie::Texture *m_sprite;
	Vector2 m_size;
	Vector2 m_origin = Vector2(0.5f, 0.5f);
};

