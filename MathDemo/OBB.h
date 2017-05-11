#pragma once
#include "Node.h"
#include <Vector2.h>
#include <vector>

class OBB : public Node {
public:
	OBB();
	OBB(float width, float height);
	~OBB();

	virtual void render(aie::Renderer2D *renderer);
	void updatePointsByMatrix(float *worldMat);
	
	/**Calculate the normals for each of the faces*/
	std::vector<Vector2<float>> calculateFaceNormals();
	bool isBetweenOrdered(float val, float lowerBound, float upperBound);

	/**Calculate the minimum and maximum vertices along a vector*/
	void calcMinMax(const Vector2<float>& axis, float &min, float &max);
	/**Check if a point is within the bounding region*/
	bool contains(Vector2<float> &point);
	/**Check if a line intersects the collider box*/
	bool intersects(/*line*/) {}
	/**Check if we collide with another collider box*/
	bool collides(OBB &rhs);

protected:
	Vector2<float> m_size;

	// Store the points clockwise from topleft
	// {topLeft, topRight, bottomRight, bottomLeft}
	std::vector<Vector2<float>> m_points;
};