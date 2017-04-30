
#include <Matrix3.h>
#include <Texture.h>
#include <Renderer2D.h>
#include "Node.h"
#include "AABB.h"

AABB::AABB() {
}

AABB::AABB(float x, float y, float width, float height) {
	translate(Vector2(x, y));
	m_size = Vector2(width, height);
}


AABB::~AABB() {
}

void AABB::render(aie::Renderer2D * renderer) {
	if (m_debugDraw) {
		Matrix3 gMat = calculateGlobalTransform();
		Vector2 pos = gMat.getTranslation();

		renderer->setRenderColour(0xff000080);
		renderer->drawBox(pos.x, pos.y, m_size.x, m_size.y);
		renderer->setRenderColour(0xffffffff);
	}
}

void AABB::updateSizeByRotation(float spriteRotation) {
	Vector2 prevSize = m_size;
	m_size = Vector2(	m_size.x + (prevSize.x * cosf(spriteRotation)) + (prevSize.y * sinf(spriteRotation)),
						m_size.y + (prevSize.x * sinf(spriteRotation)) + (prevSize.y * cosf(spriteRotation)));
}

void AABB::setSize(const Vector2 & size) {
	m_size = size;
}

Vector2 & AABB::getSize() {
	return m_size;
}
