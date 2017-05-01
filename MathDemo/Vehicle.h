#pragma once
#include "GameEntity.h"

class Vehicle : public GameEntity {
public:
	Vehicle();
	Vehicle(aie::Texture *tex);
	~Vehicle();
};

