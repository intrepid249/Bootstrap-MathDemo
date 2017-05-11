#pragma once
#include "Node.h"
#include <Vector2.h>
#include <vector>

class OBB : public Node {
public:
	OBB();
	/** Construct a bounding box with a set width and height*/
	OBB(float width, float height);
	~OBB();

	/** Overload the parent's render  function
	* @param renderer - pointer to an instance of the graphics renderer*/
	virtual void render(aie::Renderer2D *renderer);
	/** Updates the corner vertices of the bounding box
	* @param worldMat - pointer to the first element of a Matrix4 world matrix*/
	void updatePointsByMatrix(float *worldMat);
	
	/** Calculate the normals for each of the faces*/
	std::vector<Vector2<float>> calculateFaceNormals();
	/** Check if a value is between two bounding values*/
	bool isBetweenOrdered(float val, float lowerBound, float upperBound);

	/** Calculate the minimum and maximum vertices along an axis vector
	* @param axis - check along this vector
	* @param min - the function will modify this value by reference
	* @param max - the function will modify this value by reference*/
	void calcMinMax(const Vector2<float>& axis, float &min, float &max);
	/** Check if a point is within the bounding region*/
	bool contains(Vector2<float> &point);
	/** Check if a line intersects the collider box*/
	bool intersects(/*line*/) {}
	/** Check if we collide with another collider box*/
	bool collides(OBB &rhs);

protected:
	Vector2<float> m_size;

	/**Store the points clockwise from topleft
	*m_points{[0]topLeft, [1]topRight, [2]bottomRight, [3]bottomLeft}*/
	std::vector<Vector2<float>> m_points;
};