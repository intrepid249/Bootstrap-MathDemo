#pragma once
#include "Node.h"
#include <vector>

class OBB : public Node {
public:
	OBB();
	OBB(float width, float height);
	~OBB();

	virtual void render(aie::Renderer2D *renderer);
	void updatePointsByMatrix(float *worldMat);

	bool contains(Vector2 &point);
	//bool intersects(line);
	bool collides(OBB &rhs);

protected:
	Vector2 m_size;

	// Store the points clockwise from topleft
	// {topLeft, topRight, bottomRight, bottomLeft}
	std::vector<Vector2> m_points;
};