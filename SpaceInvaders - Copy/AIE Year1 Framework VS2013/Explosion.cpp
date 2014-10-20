#include "Explosion.h"
#include "AIE.h"
#include <stdlib.h>


Explosion::Explosion()
{
	SetSpriteID(CreateSprite("./images/Explosion.png", 50, 50, true));
	if (rand() % 2 == 0)
	{
		spinRate = 20;
	} 
	else
	{
		spinRate = -20;
	}
}


Explosion::~Explosion()
{
}

void Explosion::Update(float delta)
{
	if (isActive){
		RotateSprite(spriteID, delta * spinRate);
		age += delta;
		if (age > 1){
			isActive = false;
		}
	}
}

void Explosion::Draw()
{
	if (isActive){
		MoveSprite(spriteID, (int)position.x, (int)position.y);
		DrawSprite(spriteID);
	}
}

