#pragma once
#include "GameEntity.h"
#include <Input.h>

class Vehicle : public GameEntity {
public:
	Vehicle();
	Vehicle(aie::Texture *tex);
	~Vehicle();

	virtual void setControls(aie::EInputCodes fwKey, aie::EInputCodes bwKey, aie::EInputCodes lKey, aie::EInputCodes rKey);
	virtual void updateControls(aie::Input *input);
	virtual void updateToFaceMouse(Vector2 &mousePos);
	virtual void update(float dt);

	virtual void render(aie::Renderer2D *renderer);

protected:
	aie::EInputCodes m_fwKey, m_bwKey, m_lKey, m_rKey;
	bool m_moveFW, m_moveBW, m_turnL, m_turnR;
};

