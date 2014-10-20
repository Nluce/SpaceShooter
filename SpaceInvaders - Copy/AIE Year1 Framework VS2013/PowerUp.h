#pragma once
#include "Entity.h"
class PowerUp :
	public Entity
{
public:
	virtual void Update(float delta);
	virtual void Draw();
	PowerUp();
	~PowerUp();
};

