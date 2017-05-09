#pragma once
#include "GameEntity.h"
#include <Input.h>
#include <Vector2.h>
#include <map>
#include "settings.h"

class Vehicle : public GameEntity {
public:
	Vehicle();
	Vehicle(aie::Texture *tex);
	virtual ~Vehicle();

	virtual void setControls(std::map<eControlID, aie::EInputCodes> controlScheme);
	virtual void updateControls(aie::Input *input);
	virtual void update(float dt);

	virtual void render(aie::Renderer2D *renderer);

	virtual void faceAtPoint(Vector2<float> &point, GameEntity *obj);

	virtual void setCamera(Vector2<float> *camPos);
	virtual void setUserControlled(bool flag);
	virtual bool isUserControlled();

protected:
	std::map<eControlID, aie::EInputCodes> m_controls;
	bool m_moveFW, m_moveBW, m_turnL, m_turnR;
	Vector2<float> m_moveSpeed;
	float m_turnSpeed;
	
	Vector2<float> *m_cameraPos;

	bool m_userControlled;
};