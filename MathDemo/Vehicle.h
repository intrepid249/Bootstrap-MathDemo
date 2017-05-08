#pragma once
#include "GameEntity.h"
#include <Input.h>
#include <Vector2.h>

class Vehicle : public GameEntity {
public:
	Vehicle();
	Vehicle(aie::Texture *tex);
	virtual ~Vehicle();

	virtual void setControls(aie::EInputCodes fwKey, aie::EInputCodes bwKey, aie::EInputCodes lKey, aie::EInputCodes rKey);
	virtual void updateControls(aie::Input *input);
	virtual void update(float dt);

	virtual void render(aie::Renderer2D *renderer);

	virtual void faceAtPoint(Vector2<float> &point, GameEntity *obj);

	virtual void setCamera(Vector2<float> *camPos);
	virtual void setUserControlled(bool flag);
	virtual bool isUserControlled();

protected:
	aie::EInputCodes m_fwKey, m_bwKey, m_lKey, m_rKey;
	bool m_moveFW, m_moveBW, m_turnL, m_turnR;
	Vector2<float> m_moveSpeed;
	float m_turnSpeed;
	
	Vector2<float> *m_cameraPos;

	bool m_userControlled = false;
};