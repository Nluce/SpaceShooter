#include "Player.h"
#include "Bullet.h"
#include "AIE.h"

bool playerIsDead = false;

void Player::SetMovementKeys(unsigned int moveLeftKey, unsigned int moveRightKey, unsigned int moveUpKey, unsigned int moveDownKey)
{
	this->moveLeftKey = moveLeftKey;
	this->moveRightKey = moveRightKey;
	this->moveUpKey = moveUpKey;
	this->moveDownKey = moveDownKey;
}
void Player::SetMovementExtremes(unsigned int leftMovementExtreme, unsigned int rightMovementExtreme,unsigned int upMovementExtreme, unsigned int downMovementExtreme)
{
	this->leftMovementExtreme = leftMovementExtreme;
	this->rightMovementExtreme = rightMovementExtreme;
	this->upMovementExtreme = upMovementExtreme;
	this->downMovementExtreme = downMovementExtreme;
}

void Player::Shoot(unsigned int textureID, float delta)
{

	if (IsKeyDown(iShootKey) && currentReloadBulletTime >= maxBulletReloadTime)
	{
		switch (iPowerUpLevel)
		{
		case 1:
			GetInactiveBullet().InitialiseBullet(position, Vector2D(0, 1000), textureID);
			currentReloadBulletTime = 0.0f;
			break;
		case 2:
			GetInactiveBullet().InitialiseBullet(position + Vector2D(10, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-10, 0), Vector2D(0, 1000), textureID);
			currentReloadBulletTime = 0.0f;
			break;
		case 3:
			GetInactiveBullet().InitialiseBullet(position + Vector2D(20, 0), Vector2D(50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(0, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-20, 0), Vector2D(-50, 1000), textureID);
			currentReloadBulletTime = 0.0f;
			break;
		case 4:
			GetInactiveBullet().InitialiseBullet(position + Vector2D(30, 0), Vector2D(50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(10, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-10, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-30, 0), Vector2D(-50, 1000), textureID);
			currentReloadBulletTime = 0.0f;
			break;
		case 5:
			GetInactiveBullet().InitialiseBullet(position + Vector2D(40, 0), Vector2D(100, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(20, 0), Vector2D(50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(0, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-20, 0), Vector2D(-50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-40, 0), Vector2D(-100, 1000), textureID);
			currentReloadBulletTime = 0.0f;
			break;
		case 6:
			GetInactiveBullet().InitialiseBullet(position + Vector2D(50, 0), Vector2D(100, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(30, 0), Vector2D(50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(10, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-10, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-30, 0), Vector2D(-50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-50, 0), Vector2D(-100, 1000), textureID);
			currentReloadBulletTime = 0.0f;
			break;
		case 7:
			GetInactiveBullet().InitialiseBullet(position + Vector2D(40, 0), Vector2D(100, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(20, 0), Vector2D(50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(0, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-20, 0), Vector2D(-50, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-40, 0), Vector2D(-100, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(10, 0), Vector2D(0, 1000), textureID);
			GetInactiveBullet().InitialiseBullet(position + Vector2D(-10, 0), Vector2D(0, 1000), textureID);
			currentReloadBulletTime = 0.0f;
			break;
		}

		
	}

	currentReloadBulletTime += delta;
}

Bullet& Player::GetInactiveBullet()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!bullets[i].isActive)
		{
			return bullets[i];
		}
	}

	return bullets[0];
}

void Player::Update(float delta)
{
	if (playerIsDead)
	{
		return;
	}
	if (IsKeyDown(moveLeftKey))
	{
		position.x -= delta * speed;
		if (position.x < (leftMovementExtreme + size.x*.5f))
		{
			position.x = (leftMovementExtreme + size.x*.5f);
		}
	}

	if (IsKeyDown(moveRightKey))
	{
		position.x += delta * speed;
		if (position.x >(rightMovementExtreme - size.x*.5f))
		{
			position.x = (rightMovementExtreme - size.x*.5f);
		}
	}
	if (IsKeyDown(moveUpKey))
	{
		position.y += delta * speed;
		if (position.y > (upMovementExtreme - size.y*.5f))
		{
			position.y = (upMovementExtreme - size.y*.5f);
		}
	}

	if (IsKeyDown(moveDownKey))
	{
		position.y -= delta * speed;
		if (position.y <(downMovementExtreme + size.y*.5f))
		{
			position.y = (downMovementExtreme + size.y*.5f);
		}
	}
}

void Player::Draw()
{
	if (!playerIsDead)
	{
		MoveSprite(spriteID, (int)position.x, (int)position.y);
		DrawSprite(spriteID);
	}
	
}

void Player::SetSpeed(float speed)
{
	this->speed = speed;
}

float Player::GetSpeed()
{
	return speed;
}

Player::Player()
{
	currentReloadBulletTime = 0.0f;
	maxBulletReloadTime = 0.25f;
}

Player::~Player()
{

}
