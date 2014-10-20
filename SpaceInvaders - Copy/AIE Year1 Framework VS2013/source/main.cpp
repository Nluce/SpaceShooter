#include "AIE.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "sharedgamedata.h"
#include "StateManager.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Vector2D.h"
#include "Formation.h"
#include "Explosion.h"
#include "PowerUp.h"
#include "EnemyBullet.h"
#include "Background.h"
using namespace std;

const char* pInvadersFont = "./fonts/invaders.fnt";//font
char pkGameOver[] = "GAME OVER";
char pkGoToMainMenu[] = "Press M to return to Main Menu";
char pkInsertCoins[] = "press enter to start!";
void Reset();


int lives = 2;
std::vector<Entity*> gameObjects;         //New Version
std::vector<Entity*> explosions;         //New Version
std::vector<Entity*> powerUps;
std::vector<Entity*> enemyBullets;


float fTotalTime = 0.0f;
float fPlayerSpawnTime = 0.0f;
int iEnemiesCreated = 0;
int iEnemyGroupsAdded = 0;
float PlayerRespawnTime;
int iSmallEnemiesCreated = 0;

typedef enum{
	KK_ESC = 256,
	KK_ENTER = 257,
	KK_LEFT = 263,
	KK_RIGHT = 262,
};

int RandomInt(int max)
{
	return rand() % max;
}

float RandomFloat()
{
	return (float) rand() / (float)RAND_MAX;
}

float RandomFloat(float max)
{
	return RandomFloat() * max;
}
float RandomFloat(float min, float max)
{
	return RandomFloat(max - min) + min;

}
unsigned int iLeftMovementExtreme;
unsigned int iRightMovementExtreme;
void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_RightExtreme)
{
	iLeftMovementExtreme = a_leftExtreme;
	iRightMovementExtreme = a_RightExtreme;
}



void UpdateMainMenu();
void UpdateGameState();

unsigned int iArcadeMarquee;
//Player global variables

float fPlayerX;
float fPlayerY;;
int iEnemyWidth = 64;
int iEnemyHeight = 32;
int fPlayerWidth = 92;
int fPlayerHeight = 48;

Enemy * GetInactiveEnemy()
{
	// look for an inactive enemy ship in the game objects
	for (auto object : gameObjects){
		Enemy* enemyShip = dynamic_cast<Enemy*>(object);
		if (enemyShip != 0){
			if (!enemyShip->GetIsActive()){
				// we found one... return it
				return enemyShip;
			}
		}
	}

	// did not find any inactive ships...
	// make a new one
	Enemy* enemy = new Enemy();
	// add it to the list
	gameObjects.push_back(enemy);

	// return it
	return enemy;
}
EnemyBullet* GetInactiveEnemyBullet()
{
	// look for an inactive enemy ship in the game objects
	for (auto object : enemyBullets){
		EnemyBullet* enemyBullet = dynamic_cast<EnemyBullet*>(object);
		if (enemyBullet != 0){
			if (!enemyBullet->GetIsActive()){
				// we found one... return it
				return enemyBullet;
			}
		}
	}

	// did not find any inactive ships...
	// make a new one
	EnemyBullet* enemyBullet = new EnemyBullet();
	// add it to the list
	enemyBullets.push_back(enemyBullet);

	// return it
	return enemyBullet;
}
void CreateEnemyBullet(Vector2D position)
{
	EnemyBullet* enemyBullet = GetInactiveEnemyBullet();
	enemyBullet->SetPosition(position);
	enemyBullet->SetIsActive(true);
	enemyBullet->SetVelocity(Vector2D(0, -400));
}

Explosion * GetInactiveExplosion()
{
	// look for an inactive explosion in the game objects
	for (auto object : explosions){
		Explosion* explosion = dynamic_cast<Explosion*>(object);
		if (explosion != 0){
			if (!explosion->GetIsActive()){
				// we found one... return it
				return explosion;
			}
		}
	}

	// did not find any inactive explosion...
	// make a new one
	Explosion* explosion = new Explosion();
	// add it to the list
	explosions.push_back(explosion);

	// return it
	return explosion;
}

void CreateExplosion(Vector2D position)
{
	Explosion * explosion = GetInactiveExplosion();
	explosion->Start(position);
}

PowerUp * GetInactivePowerUp()
{
	// look for an inactive explosion in the game objects
	for (auto object : powerUps){
		PowerUp* powerUp = dynamic_cast<PowerUp*>(object);
		if (powerUp != 0){
			if (!powerUp->GetIsActive()){
				// we found one... return it
				return powerUp;
			}
		}
	}

	// did not find any inactive explosion...
	// make a new one
	PowerUp* powerUp = new PowerUp();
	// add it to the list
	powerUps.push_back(powerUp);

	// return it
	return powerUp;
}

void CreatePowerup(Vector2D position)
{
	PowerUp * powerUp = GetInactivePowerUp();
	powerUp->SetPosition(position);
	powerUp->SetIsActive(true);
}
void CreateEnemy(Vector2D position, Vector2D velocity)
{
	{
		Enemy* enemy = GetInactiveEnemy();
		enemy->SetSpriteID(CreateSprite("./images/EnemyShip.png", iEnemyWidth, iEnemyHeight, true));
		enemy->SetPosition(position);
		enemy->SetVelocity(velocity);
		enemy->SetIsActive(true);
		enemy->isSmall = false;
		enemy->CurrentHp = ((fTotalTime - fPlayerSpawnTime) / 20) + 1;
	}
}
void CreateSmallEnemy(Vector2D position, Vector2D velocity)
{
	{
		Enemy* enemy = GetInactiveEnemy();
		enemy->SetSpriteID(CreateSprite("./images/Enemyshipsmall.png", 18, 15, true));
		enemy->SetPosition(position);
		enemy->SetVelocity(velocity);
		enemy->SetIsActive(true);
		enemy->isSmall = true;
		enemy->CurrentHp = ((fTotalTime - fPlayerSpawnTime) / 40) + 1;
	}
}


int bulletTexture;
int score;
int direction;
float speed = 100;
Player* player;
int main(int argc, char* argv[])
{
	srand(time(0));
	//\ Lets initialise the AIE Framework and give the window it creates an appropriate title
	Initialise(iScreenWidth, iScreenHeight, false, "Space Invaders");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(pInvadersFont);
	
	score = 0;
	bulletTexture = CreateSprite("./images/PlayerBullet.png", 10, 16, true);

	iArcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", iScreenWidth, iScreenHeight, true);
	MoveSprite(iArcadeMarquee, iScreenWidth * 0.5f, iScreenHeight * 0.5f);
	//\Now lets create the sprite for our players cannon. That's right in space invaders we control a cannon
	//\So lets create that with an appropriate variable name and move it to a suitable location (say the middle of our screen)


	player = new Player();

	player->SetSize(Vector2D(fPlayerWidth, fPlayerHeight));
	player->SetMovementKeys('A', 'D','W','S');
	player->iShootKey = KEY_SPACE;
	player->SetMovementExtremes(0, iScreenWidth,iScreenHeight,0);
	player->SetSpriteID(CreateSprite("./images/ship.png", player->GetSize().x, player->GetSize().y, true));
	player->SetPosition(Vector2D(iScreenWidth * 0.5f, 80.f));
	player->SetSpeed(float(iScreenWidth / 4));
	gameObjects.push_back(player);      //Add our player object to the dynamic array	float fEnemyX = iScreenWidth * 0.2f;


	StateManager::GameStates eCurrentState = StateManager::eMAIN_MENU;
	do
	{
		float fDeltaT = GetDeltaTime();
		ClearScreen();
		switch (eCurrentState)
		{
		case StateManager::eMAIN_MENU:
			UpdateMainMenu();
			if (IsKeyDown(KK_ENTER))
			{
				Reset();
				eCurrentState = StateManager::eGAMEPLAY;
			}
			break;
		case StateManager::eGAMEPLAY:
			UpdateGameState();
			if (IsKeyDown('M'))
			{
				eCurrentState = StateManager::eMAIN_MENU;
			}
			break;
		default:
			break;
		}
	} while (FrameworkUpdate() == false);

	DestroySprite(player->GetSpriteID());
	DestroySprite(iArcadeMarquee);
	Shutdown();

	return 0;
}

void NewLife()
{
	for (auto alienShip : gameObjects)
	{
		Enemy* enemyShip = dynamic_cast<Enemy*>(alienShip);
		if (enemyShip != 0)
		{
			if (enemyShip->GetIsActive())
			{
				enemyShip->SetIsActive(false);
			}
		}
	}
	for (auto powerUp : powerUps)
	{
		powerUp->SetIsActive(false);
	}
	if (lives > 0)
	{
		player->SetPosition(Vector2D(iScreenWidth * 0.5f, 80.f));
		playerIsDead = false;
		fPlayerSpawnTime = fTotalTime;
		
	}
	else 
	{

		DrawString(pkGameOver, iScreenWidth * 0.3f, iScreenHeight * 0.6f);
		DrawString(pkGoToMainMenu, iScreenWidth * 0.2f, iScreenHeight * 0.5f);
	}
}
void Reset()
{
	fTotalTime = 0;
	lives = 2;
	NewLife();
	score = 0;
	ResetBackgrounds();
}

void UpdateMainMenu()
{
	DrawSprite(iArcadeMarquee);
	SetFont(pInvadersFont);

	DrawString(pkInsertCoins, iScreenWidth * 0.28f, iScreenHeight * 0.5f);
	//DrawString(pkCredits, iScreenWidth * 0.25f, iScreenHeight * 0.4f);
	//DrawString(pkHiScore, iScreenWidth * 0.425f, iScreenHeight - 2);

}

bool CheckCollision(float x1, float y1, float x2, float y2, float distance)
{
	float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	if (d < distance)
		return true;
	else
		return false;
}


void PlayerLogic(Player* player, float delta)
{
	//\==================================================================================
	//\ Player movement handling code
	//\==================================================================================
	if (!playerIsDead)
	{
		player->Shoot(bulletTexture, delta);
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		player->bullets[i].Update(delta);
		player->bullets[i].Draw();
	}
	for (auto object : powerUps){
		PowerUp* powerUp = dynamic_cast<PowerUp*>(object);
		if (powerUp != 0){
			if (powerUp->GetIsActive()){
				if (player->CheckCollision(*powerUp, 40))
				{
					if (player->iPowerUpLevel < player->iPowerUpUltraSuperMax)
					{
						player->iPowerUpLevel++;
					}
					powerUp->SetIsActive(false);

				}

			
			}
		}
	}
	if (!playerIsDead)
	{

		for (auto enemyBullet : enemyBullets)
		{
			if (enemyBullet->GetIsActive())
			{

				if (player->CheckCollision(*enemyBullet, 20))
				{
					CreateExplosion(player->GetPosition());
					player->iPowerUpLevel = 1;
					enemyBullet->SetIsActive(false);
					playerIsDead = true;
					PlayerRespawnTime = fTotalTime + 2;
					lives--;
				}

			}

		}
	}
	for (auto alienShip : gameObjects)
	{
		Enemy* enemyShip = dynamic_cast<Enemy*>(alienShip);
		if (enemyShip != 0)
		{
			if (enemyShip->GetIsActive())
			{
				for (int i = 0; i < MAX_BULLETS; i++)
				{
					if (player->bullets[i].isActive) 
					{
						if (player->bullets[i].CheckCollision(*enemyShip, 30.0f))
						{
							enemyShip->CurrentHp -= 1;
							CreateExplosion(enemyShip->GetPosition());
							player->bullets[i].isActive = false;
							if (enemyShip->CurrentHp <= 0)
							{

								
								enemyShip->SetIsActive(false);
								
								score++;
								if (enemyShip->isSmall)
								{
									CreatePowerup(enemyShip->GetPosition());
								}
							}
						}
					}
				}
				if (!playerIsDead)
				{
					if (player->CheckCollision(*enemyShip, 30))
					{
						CreateExplosion(player->GetPosition());
						player->iPowerUpLevel = 1;
						enemyShip->SetIsActive(false);
						playerIsDead = true;
						PlayerRespawnTime = fTotalTime + 2;
						lives--;
					}
				}
			}
		}
	}
	
}




void CreateEnemyGroup()
{
	Vector2D position(RandomFloat(iScreenWidth), iScreenHeight * 1.1f);
	Vector2D velocity(RandomFloat(-100.0f, 100.0f), -50.0f);

	Formation * f;
	switch (RandomInt(3))
	{
	case 0:
		f = &iFormation;
		break;
	case 1:
		f = &vFormation;
		break;
	case 2:
		f = &flatFormation;
		break;
	}

	Vector2D * vectors = f->GetVectors();

	for (int i = 0; i < 5; i++){
		CreateEnemy(position + vectors[i], velocity);
	}

}




void UpdateGameState()
{
	SetFont(pInvadersFont);
	float fDeltaT = GetDeltaTime();
	fTotalTime += fDeltaT;
	if (iSmallEnemiesCreated * 15 < fTotalTime)
	{
		Vector2D position(RandomFloat(iScreenWidth), iScreenHeight * 1.1f);
		Vector2D velocity(RandomFloat(-100.0f, 100.0f), -100.0f);
		CreateSmallEnemy(position,velocity);
		iSmallEnemiesCreated++;
	}
	if (iEnemyGroupsAdded * 5 < fTotalTime)
	{
		CreateEnemyGroup();
		iEnemyGroupsAdded++;
	}
	if (playerIsDead)
	{
		if (PlayerRespawnTime < fTotalTime)
		{
			NewLife();
		}
	}
	// draw and update the explosions
	DrawBackgrounds(iScreenWidth, iScreenHeight, player, fDeltaT, fTotalTime);
	for (auto object : explosions)
	{
		object->Update(fDeltaT);
		object->Draw();
	}
	for (auto object : enemyBullets)
	{
		object->Update(fDeltaT);
		object->Draw();

	}
	for (auto object : powerUps)
	{
		object->Update(fDeltaT);
		object->Draw();
	}
	for (auto object : gameObjects)
	{
		//Determine the type at runtime
		if (dynamic_cast<Player*>(object) != 0)
		{
			//Process player-specific logic
			PlayerLogic(dynamic_cast<Player*>(object), fDeltaT);
		}

		//Update and draw our objects
		object->Update(fDeltaT);
		object->Draw();
	}



	SetFont(pInvadersFont);


	
	char buffer[50];
	sprintf(buffer, "EXTRA LIVES = %d", lives);
	DrawString(buffer, 10, 30);

	sprintf(buffer, "SCORE = %d", score);
	DrawString(buffer, 10, iScreenHeight - 10);

	
	//for (int i = 256; i < 512; i++){
	//	if (IsKeyDown(i)){
	//		char buffer[20];
	//		sprintf(buffer, "%d", i);
	//		DrawString(buffer, iScreenWidth * 0.7f, 99);
	//	}
	//}

}
