#pragma once
#include "Entity.h"
#include "Player.h"

void DrawBackgrounds(int iScreenWidth, int iScreenHeight, Player* player, float fDeltaT, float fTotalTime);
void ResetBackgrounds();

class Background :
	public Entity
{
	int serialNumber;
public:
	virtual void Update(float delta);
	virtual void Draw();
	void Start();
	void Update(float x, float totalTime);
	Background();
	~Background();
};

