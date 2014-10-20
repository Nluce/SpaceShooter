#include "Entity.h"

Entity::Entity()
{
}


void Entity::SetSpriteID(unsigned int spriteID)
{
	this->spriteID = spriteID;
}

unsigned int Entity::GetSpriteID()
{
	return spriteID;
}




Entity::~Entity()
{
}