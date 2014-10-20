#include "Enemy.h"
#include <math.h>
#include "sharedgamedata.h"
Enemy::Enemy()
{
	isActive = true;
}

void Enemy::Update(float delta)
{
	if (isActive)
	{
		position += velocity * delta;

		if (position.x < 0)
		{
			position.x = 0;
			velocity.x = abs(velocity.x);
		}
		if (position.x > iScreenWidth)
		{
			position.x = iScreenWidth;
			velocity.x = -abs(velocity.x);
		}
		if (position.y < 0)
		{
			isActive = false;
		}
		if (RandomFloat(20.0f) < delta)
		{
			CreateEnemyBullet(position);
		}
	}
}



void Enemy::Draw()
{
	if (isActive)
	{
		MoveSprite(spriteID, position.x, position.y);
		DrawSprite(spriteID);
	}
}

Enemy::~Enemy()
{
}