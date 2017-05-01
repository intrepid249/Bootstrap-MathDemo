#pragma once
#include "Node.h"

class OBB : public Node {
public:
	OBB();
	OBB(float width, float height);
	~OBB();

	void updatePoints();

	bool contains(Vector2 &point);
	//bool intersects(line);
	bool collides(OBB &rhs);

protected:
	Vector2 m_size;
};