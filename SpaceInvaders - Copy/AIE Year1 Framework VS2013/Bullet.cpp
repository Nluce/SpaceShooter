#include "Bullet.h"

Bullet::Bullet()
{
	isActive = false;
}

void Bullet::Draw()
{
	if (isActive)
	{
		MoveSprite(textureID, position.GetX(), position.GetY());
		DrawSprite(textureID);
	}
}

void Bullet::Update(float delta)
{
	if (isActive)
	{
		position += velocity*delta;
		if (position.y > 1000)
		{
			isActive = false;
		}
	}
}

void Bullet::InitialiseBullet(Vector2D p, Vector2D v, unsigned int textureID)
{
	this->textureID = textureID;
	position = p;
	velocity = v;

	isActive = true;
}


Bullet::~Bullet()
{
}