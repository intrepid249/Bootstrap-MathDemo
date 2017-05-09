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


	Vector2<float> averagePoint();

	// Check if a point is within the bounding region
	bool contains(Vector2<float> &point);
	// Check if a line intersects the collider box
	bool intersects(/*line*/) {}
	// Check if we collide with another collider box
	bool collides(OBB &rhs);


protected:
	Vector2<float> m_size;

	// Store the points clockwise from topleft
	// {topLeft, topRight, bottomRight, bottomLeft}
	std::vector<Vector2<float>> m_points;
};