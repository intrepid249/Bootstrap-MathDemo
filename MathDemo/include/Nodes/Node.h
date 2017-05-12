#pragma once
#include <Matrix3.h>
#include <Vector2.h>

namespace aie {
	class Renderer2D;
	class Texture;
}

class OBB;

/** A point in space that stores a transformation matrix
* @author Jack McCall*/
class Node {
public:
	Node();
	virtual ~Node();

	/** Update changes to the object per frame
	* @param dt - amount of time since last frame*/
	virtual void update(float dt);
	/** Draw to the screen buffer
	* @param renderer - pointer to the instance of the graphics renderer*/
	virtual void render(aie::Renderer2D *renderer);

	/** Get a pointer to the collider box*/
	virtual OBB* getCollider();

	/** Get a pointer to the particle texture*/
	virtual aie::Texture* getParticleType();

	/** Get a particle type*/
	virtual aie::Texture* getTexture();

	/** Set the upper-heirachy for coupling transform calculations*/
	void setParent(Node *parent);

	/** Sets the draw flag for the object*/
	void setDrawn(bool flag);
	/** Gets the draw flag for the object, used to check the 'alive' or 'active' status of an object*/
	bool isDrawn();

	/** Get the local transform matrix*/
	Matrix3<float> &getTransform();
	/** Calculate the global transformation matrix*/
	Matrix3<float> calculateGlobalTransform() const;

	/** Adjust the size of the object using the local matrix*/
	void scale(const Vector2<float>& size);
	/** Adjust the position of the local matrix*/
	void translate(const Vector2<float> &translation);
	/** Adjust the rotation of the local matrix*/
	void rotate(float radians);
	/** Change the rotation of the local matrix*/
	void setRotate(float radians);

	/** Get the local position*/
	Vector2<float> getLocPos();
	/** Get the local rotation*/
	float getLocRot();

protected:
	Node *m_parent = nullptr;
	Matrix3<float> m_local;
	bool m_isDrawn = true;
};

