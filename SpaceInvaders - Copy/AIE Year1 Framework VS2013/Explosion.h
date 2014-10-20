#pragma once
#include "Entity.h"
class Explosion :
	public Entity
{
	float age = 0;
	float spinRate;
public:
	virtual void Update(float delta);
	virtual void Draw();

	Explosion();
	~Explosion();


	void Start(Vector2D position){
		SetPosition(position);
		age = 0;
		isActive = true;
	}
};

