#pragma once
#include "Nodes/Node.h"

namespace aie {
	class Texture;
}

/**
*Inherits from Node to store a location matrix and Node's methods
*Implements additional functionality to allow storage and rendering
   of sprites*/
class SpriteNode : public Node {
public:
	SpriteNode();
	SpriteNode(aie::Texture *m_tex);
	~SpriteNode();

	/*Overload the parent's render function*/
	virtual void render(aie::Renderer2D * renderer);

	/*Set the size of the Sprite Node*/
	void setSize(const Vector2<float> &size);
	/*Get the size of the Sprite Node*/
	Vector2<float>& getSize();

	/*Set the rendering offset of the Sprite Node*/
	void setOrigin(const Vector2<float> &origin);
	/*Get the rendering offset of the Sprite Node*/
	Vector2<float>& getOrigin();

protected:
	aie::Texture *m_sprite;
	Vector2<float> m_size;
	Vector2<float> m_origin = Vector2<float>(0.5f, 0.5f);
};

