#pragma once
#include "Entities/GameEntity.h"
#include <Input.h>
#include <Vector2.h>
#include <map>
#include "settings.h"

/** An object that allows for movement input dependent on if the user has control
* @author Jack McCall*/
class Vehicle : public GameEntity {
public:
	Vehicle();
	/** Create a new vehicle object
	* @param tex - the image to use for the vehicle's chassis*/
	Vehicle(aie::Texture *tex);
	virtual ~Vehicle();


	/** Set the control scheme for the vehicle
	* @param controlScheme - a key/value pair list of the Control ID code and the Input Key Codes*/
	virtual void setControls(std::map<eControlID, aie::EInputCodes> controlScheme);
	/** Updates the movement flags per frame depending on input signals received
	* @param input - pointer to an instance of the input handle*/
	virtual void updateControls(aie::Input *input);
	/** Overloads the parent's update function
	* @see MathDemo::Node#update(float)*/
	virtual void update(float dt);
	/** Overloads the parent's render function
	* @see MathDemo::Node#render(aie::Renderer2D)*/
	virtual void render(aie::Renderer2D *renderer);

	/** Set's the rotation of an object to face a particular point
	* @param point - the point to look at
	* @param obj - a pointer to the object to rotate*/
	virtual void faceAtPoint(Vector2<float> &point, GameEntity *obj);

	/** Sets the position of the camera
	* @param camPos - pointer to the camera's position value to modify*/
	virtual void setCamera(Vector2<float> *camPos);
	/** Sets whether or not the user has control of the vehicle and if we
	will update for the input received*/
	virtual void setUserControlled(bool flag);
	/** Returns the current state of vehicle control*/
	virtual bool isUserControlled();

protected:
	std::map<eControlID, aie::EInputCodes> m_controls;	// The stored key/value pair list of the control scheme
	bool m_moveFW, m_moveBW, m_turnL, m_turnR;			// Movement flag
	Vector2<float> m_moveSpeed;							
	float m_turnSpeed;									

	Vector2<float> *m_cameraPos;						// Store a pointer to the camera position for modification

	bool m_userControlled;								// Whether or not the vehicle will accept user input
};