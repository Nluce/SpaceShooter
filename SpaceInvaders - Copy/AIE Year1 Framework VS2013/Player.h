#include "Bullet.h"
#include "Entity.h"

const int MAX_BULLETS = 50;

extern float currentReloadBulletTime;
extern float maxBulletReloadTime;

extern bool playerIsDead;
#pragma once
class Player : public Entity
{
public:

	void SetMovementKeys(unsigned int moveLeftKey, unsigned int moveRightKey, unsigned int moveUpKey, unsigned int moveDownKey);
	void SetMovementExtremes(unsigned int leftMovementExtreme, unsigned int rightMovementExtreme, unsigned int upMovementExtreme, unsigned int downMovementExtreme);

	//We must implement these methods before we can instantiate the class
	virtual void Update(float delta);
	virtual void Draw();

	void Shoot(unsigned int textureID, float delta);
	Bullet& GetInactiveBullet();

	void SetSpeed(float speed);
	float GetSpeed();

	Bullet bullets[MAX_BULLETS];

	Player();
	~Player();
	int iPowerUpLevel = 1;
	int iPowerUpUltraSuperMax = 7;
	unsigned int iShootKey;

private:

	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	unsigned int moveUpKey;
	unsigned int moveDownKey;

	float speed;

	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;
	unsigned int upMovementExtreme;
	unsigned int downMovementExtreme;

	float currentReloadBulletTime;
	float maxBulletReloadTime;
};