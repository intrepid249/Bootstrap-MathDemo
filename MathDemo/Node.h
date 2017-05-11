#pragma once
#include <Matrix3.h>
#include <Vector2.h>

namespace aie {
	class Renderer2D;
}

class OBB;

class Node {
public:
	Node();
	virtual ~Node();

	virtual void update(float dt);
	virtual void render(aie::Renderer2D *renderer);

	virtual OBB* getCollider();
	//virtual bool checkCollision(std::vector<Node*> objects);

	void setParent(Node *parent);

	void setDrawn(bool flag);
	bool isDrawn();

	Matrix3<float> &getTransform();
	Matrix3<float> calculateGlobalTransform() const;

	void scale(const Vector2<float>& size);
	void translate(const Vector2<float> &translation);
	void rotate(float radians);
	void setRotate(float radians);

	Vector2<float> getLocPos();
	float getLocRot();

protected:
	Node *m_parent = nullptr;
	Matrix3<float> m_local;
	bool m_isDrawn = true;
};

