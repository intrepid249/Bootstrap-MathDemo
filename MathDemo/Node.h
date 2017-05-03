#pragma once
#include <Matrix3.h>

class Vector2;
namespace aie {
	class Renderer2D;
}

class Node {
public:
	Node();
	virtual ~Node();

	virtual void update(float dt);
	virtual void render(aie::Renderer2D *renderer);

	void setParent(Node *parent);

	void setDrawn(bool flag);
	bool isDrawn();

	Matrix3 &getTransform();
	Matrix3 calculateGlobalTransform() const;

	void translate(const Vector2 &translation);
	void rotate(float radians);
	void setRotate(float radians);

	Vector2 getLocPos();
	float getLocRot();

protected:
	Node *m_parent = nullptr;
	Matrix3 m_local;
	bool m_isDrawn = true;
};

