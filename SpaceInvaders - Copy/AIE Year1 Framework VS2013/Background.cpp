#include "Background.h"
#include "AIE.h"
#include <vector>
#include "Player.h"
#include <iostream>

using namespace std;

const float backgroundDropSpeed = 150;
const float backgroundWidth = 672 * 1.4;
const float backgroundHeight = 1996 * 1.4;
const float backgroundLifespan = backgroundHeight / backgroundDropSpeed;

int backgroundsCreated = 0;
vector<Background*> backgrounds;
int masterSpriteID;
bool masterSpriteCreated = false;

void ResetBackgrounds()
{
	for (auto bg : backgrounds)
	{
		bg->SetIsActive(false);
	}
	backgroundsCreated = 0;
}

Background * GetInactiveBackground()
{
	// look for an inactive background in the game objects
	for (auto background : backgrounds){
		if (!background->GetIsActive()){
			// we found one... return it
			return background;
		}
	}

	// did not find any inactive background...
	// make a new one
	Background* background = new Background();
	// add it to the list
	backgrounds.push_back(background);

	// return it
	return background;
}

void CreateBackground(int iScreenWidth, float fTotalTime)
{
	Background * background = GetInactiveBackground();
	background->Start();
	
}

void Background::Start()
{
	isActive = true;
	serialNumber = backgroundsCreated++;
}

Background::Background()
{
	if (!masterSpriteCreated)
	{
		masterSpriteID = CreateSprite("./images/SpaceBackground.png", backgroundWidth,backgroundHeight, true);
		masterSpriteCreated = true;
	}
	SetSpriteID(DuplicateSprite(masterSpriteID));
	SetSize(Vector2D(backgroundWidth, backgroundHeight));
	SetVelocity(Vector2D(0, -backgroundDropSpeed));
}

 void DrawBackgrounds(int iScreenWidth, int iScreenHeight, Player* player, float fDeltaT, float fTotalTime)
 {
	 if (fTotalTime >= backgroundsCreated * backgroundLifespan - iScreenHeight / backgroundDropSpeed)
	 {
		 cout << "creating badckground #" << backgroundsCreated << endl;
		 CreateBackground(iScreenWidth, fTotalTime);
	 }

	 float playerX = player->GetPosition().x;
	 float m = backgroundWidth - iScreenWidth;
	 float f = playerX / iScreenWidth;
	 float x = backgroundWidth / 2 - f * m;

	 for (auto bg : backgrounds)
	 {
		 bg->Update(x, fTotalTime);
		 bg->Draw();
	 }
 }

Background::~Background()
{
}

void Background::Update(float delta)
{
	// dont to anything here...
}
void Background::Update(float x, float fTotalTime)
{
	if (isActive)
	{
		float offset = serialNumber * backgroundHeight;
		float offset2 = fTotalTime * backgroundDropSpeed;
		float y = backgroundHeight / 2 + offset - offset2;

		if (y + backgroundHeight / 2 < 0)
		{
			cout << "destroy" << endl;
			isActive = false;
		}

		position = Vector2D(x, y);
	}
}

void Background::Draw()
{
	if (isActive){
		MoveSprite(spriteID, (int)position.x, (int)position.y);
		DrawSprite(spriteID);
	}
}