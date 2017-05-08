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

	virtual void renderStaticRotation(aie::Renderer2D *renderer);
	virtual void render(aie::Renderer2D * renderer);

	void setSize(const Vector2<float> &size);
	Vector2<float>& getSize();

	void setOrigin(const Vector2<float> &origin);
	Vector2<float>& getOrigin();

protected:
	aie::Texture *m_sprite;
	Vector2<float> m_size;
	Vector2<float> m_origin = Vector2<float>(0.5f, 0.5f);
};

