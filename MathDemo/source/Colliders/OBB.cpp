#include "Colliders/OBB.h"
#include <Vector2.h>
#include <Renderer2D.h>
#include <Utility.h>

#include <iostream>

OBB::OBB() {}

OBB::OBB(float width, float height) : m_size(Vector2<float>(width, height)) 
{
	for (int i = 0; i < 4; i++)
		m_points.push_back(Vector2<float>());
}

OBB::~OBB() {}

void OBB::render(aie::Renderer2D *renderer) {
	#ifdef _DEBUG
		// Draw the vertices
		renderer->setRenderColour(0xff0000ff);
		for (size_t i = 0; i < m_points.size(); ++i) {
			Vector2<float> p = m_points[i];
			renderer->drawBox(p.x, p.y, 3, 3);
		}
		// Draw the collider box outline
		renderer->drawLine(m_points[0].x, m_points[0].y, m_points[1].x, m_points[1].y);
		renderer->drawLine(m_points[1].x, m_points[1].y, m_points[2].x, m_points[2].y);
		renderer->drawLine(m_points[2].x, m_points[2].y, m_points[3].x, m_points[3].y);
		renderer->drawLine(m_points[3].x, m_points[3].y, m_points[0].x, m_points[0].y);

		// Draw the face normals
		renderer->setRenderColour(0x00f080ff);
		Vector2<float> pos = calculateGlobalTransform().getTranslation();
		std::vector<Vector2<float>> faceNormals = calculateFaceNormals();
		renderer->drawLine(faceNormals[0].x + pos.x, faceNormals[0].y + pos.y, pos.x, pos.y);
		renderer->drawLine(faceNormals[1].x + pos.x, faceNormals[1].y + pos.y, pos.x, pos.y);
		renderer->drawLine(faceNormals[2].x + pos.x, faceNormals[2].y + pos.y, pos.x, pos.y);
		renderer->drawLine(faceNormals[3].x + pos.x, faceNormals[3].y + pos.y, pos.x, pos.y);


		renderer->setRenderColour(0xffffffff);
	#endif // _DEBUG
}

void OBB::updatePointsByMatrix(float  *worldMat) {
	float width = m_size.x;		float height = m_size.y;
	float xOrigin = 0.5f;		float yOrigin = 0.5f;

	float tlX = (0.0f - xOrigin) * width;		float tlY = (0.0f - yOrigin) * height;
	float trX = (1.0f - xOrigin) * width;		float trY = (0.0f - yOrigin) * height;
	float brX = (1.0f - xOrigin) * width;		float brY = (1.0f - yOrigin) * height;
	float blX = (0.0f - xOrigin) * width;		float blY = (1.0f - yOrigin) * height;


	float x, y;
	x = tlX; y = tlY;
	tlX = x * worldMat[0] + y * worldMat[3] + worldMat[6];
	tlY = x * worldMat[1] + y * worldMat[4] + worldMat[7];
	m_points[0] = Vector2<float>(tlX, tlY);

	x = trX; y = trY;
	trX = x * worldMat[0] + y * worldMat[3] + worldMat[6];
	trY = x * worldMat[1] + y * worldMat[4] + worldMat[7];
	m_points[1] = Vector2<float>(trX, trY);

	x = brX; y = brY;
	brX = x * worldMat[0] + y * worldMat[3] + worldMat[6];
	brY = x * worldMat[1] + y * worldMat[4] + worldMat[7];
	m_points[2] = Vector2<float>(brX, brY);

	x = blX; y = blY;
	blX = x * worldMat[0] + y * worldMat[3] + worldMat[6];
	blY = x * worldMat[1] + y * worldMat[4] + worldMat[7];
	m_points[3] = Vector2<float>(blX, blY);
}

std::vector<Vector2<float>> OBB::calculateFaceNormals() {
	std::vector<Vector2<float>> temp;
	//North
	temp.push_back(LinearHalf(m_points[0], m_points[1]));
	//East
	temp.push_back(LinearHalf(m_points[1], m_points[2]));
	//South
	temp.push_back(LinearHalf(m_points[2], m_points[3]));
	//West
	temp.push_back(LinearHalf(m_points[3], m_points[0]));

	return temp;
}

bool OBB::contains(Vector2<float> & point) {
	Vector2<float> pos = m_parent->getLocPos();

	if (point.x < pos.x-m_size.x / 2 || point.x > pos.x+m_size.x / 2) return false;
	if (point.y < pos.y-m_size.y / 2 || point.y > pos.y+m_size.y / 2) return false;

	return true;
}

bool OBB::collides(OBB & rhs) {
	std::vector<Vector2<float>> faceNormals = calculateFaceNormals();

	Vector2<float> pos = calculateGlobalTransform().getTranslation();
	
	for (size_t i = 0; i < faceNormals.size(); ++i) {
		if (!rhs.contains(Vector2<float>(pos.x + faceNormals[i].x, pos.y + faceNormals[i].y)))
			return false;
	}


	return true;
}