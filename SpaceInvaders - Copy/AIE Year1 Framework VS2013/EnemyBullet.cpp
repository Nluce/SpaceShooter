#include "EnemyBullet.h"
#include "AIE.h"

EnemyBullet::EnemyBullet()
{
	SetSpriteID(CreateSprite("./images/enemyBullet.png", 20, 32,true));
}


EnemyBullet::~EnemyBullet()
{
}
void EnemyBullet::Update(float delta)
{
	if (isActive)
	{
		position += velocity * delta;

		if (position.y < 0)
		{
			isActive = false;
		}
	}

}


void EnemyBullet::Draw()
{
	if (isActive){
		MoveSprite(spriteID, (int)position.x, (int)position.y);
		DrawSprite(spriteID);
	}
}
