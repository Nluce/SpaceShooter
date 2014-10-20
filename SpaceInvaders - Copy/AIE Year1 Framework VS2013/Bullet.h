#include "AIE.h"
#include "Vector2D.h"
#include "Entity.h"

#pragma once
class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();

	Vector2D velocity;

	unsigned int textureID;

	

	void Update(float delta);
	void Draw();
	void InitialiseBullet(Vector2D p, Vector2D v, unsigned int textureID);

	bool isActive;
};
