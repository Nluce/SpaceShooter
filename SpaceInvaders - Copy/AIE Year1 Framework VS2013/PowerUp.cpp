#include "PowerUp.h"
#include "AIE.h"

PowerUp::PowerUp()
{
	SetSpriteID(CreateSprite("./images/PowerUp.png", 80, 80, true));
}


PowerUp::~PowerUp()
{
}
void PowerUp::Update(float delta)
{
	if (isActive)
	{

	}

}


void PowerUp::Draw()
{
	if (isActive){
		MoveSprite(spriteID, (int)position.x, (int)position.y);
		DrawSprite(spriteID);
	}
}
