#pragma once
#include "Node.h"
#include <Vector2.h>
class Matrix3;

namespace aie {
	class Texture;
	class Renderer;
}

class AABB : public Node {
public:
	AABB();
	AABB(float x, float y, float width, float height);
	~AABB();

	void render(aie::Renderer2D *renderer);

	void updateSizeByRotation(float spriteRotation);

	void setSize(const Vector2& size);
	Vector2& getSize();

protected:
	Vector2 m_size;
};

