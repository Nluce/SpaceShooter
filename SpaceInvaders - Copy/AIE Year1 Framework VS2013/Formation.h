#pragma once
#include "Vector2D.h"

class Formation
{
	Vector2D vectors[5];
public:
	Formation(Vector2D vectors[5])
	{
		for (int i = 0; i < 5; i++){
			this->vectors[i] = vectors[i];
		}
	}

	~Formation()
	{
	}

	Vector2D * GetVectors(){
		return vectors;
	}
};


extern Formation vFormation;
extern Formation iFormation;
extern Formation flatFormation;

