#include "Vector2D.h"

enum {
	eRight,
	eDownRight,
	eLeft,
	eDownLeft,
};
// the speed of the enemies
extern float enemySpeed;
// keep track of the enemy direction
extern int enemyDirection;

// this is how much we increase the enemy speed each time an enemy hits an edge.
const float enemySpeedIncrement = 10;

// this is how far down the enemies drop when they hit the screen edge.
const float enemyDropDistance = 16;

const int iScreenWidth = 672;
const int iScreenHeight = 780;
const float edgeBoundry = 50;
float RandomFloat(float max);
void CreateEnemyBullet(Vector2D position);