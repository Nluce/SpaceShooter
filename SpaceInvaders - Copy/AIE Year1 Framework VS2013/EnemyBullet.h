#pragma once
#include "Entity.h"
class EnemyBullet :
	public Entity
{
public:
	virtual void Update(float delta);
	virtual void Draw();
	EnemyBullet();
	~EnemyBullet();
};

