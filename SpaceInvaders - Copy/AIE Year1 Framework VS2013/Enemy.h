#pragma once

#include "AIE.h"
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	bool isSmall;
	virtual void Update(float delta);
	virtual void Draw();
	int CurrentHp;
	

	~Enemy();

private:

	

};