#pragma once
#include "Vector2D.h"
class Entity
{
public:
	Entity();

	void SetSize(Vector2D s)
	{
		size = s;
	}

	void SetPosition(Vector2D p)
	{
		position = p;
	}

	virtual void Update(float delta) = 0;
	virtual void Draw() = 0;

	void SetSpriteID(unsigned int spriteID);
	unsigned int GetSpriteID();

	Vector2D GetSize()
	{
		return size;
	}

	Vector2D GetPosition()
	{
		return position;
	}

	Vector2D GetVelocity()
	{
		return velocity;
	}

	void SetVelocity(Vector2D v)
	{
		velocity = v;
	}


	~Entity();
	bool CheckCollision(Entity const& o, float d)
	{
		return (position - o.position).DistanceSquared() <= d*d;
	}

	void SetIsActive(bool isActive)
	{
		this->isActive = isActive;
	}
	bool GetIsActive()
	{
		return isActive;
	}
	
protected:
	bool isActive;
	unsigned int spriteID;

	Vector2D size;
	Vector2D position;
	Vector2D velocity;
};