#include "Formation.h"


Vector2D v[] = {
	Vector2D(0, 0),
	Vector2D(50, 50),
	Vector2D(100, 100),
	Vector2D(-50, 50),
	Vector2D(-100, 100),
};

Vector2D i[] = {
	Vector2D(0, 0),
	Vector2D(0, 50),
	Vector2D(0, 100),
	Vector2D(0, 150),
	Vector2D(0, 200),
};

Vector2D flat[] = {
	Vector2D(0, 0),
	Vector2D(50, 0),
	Vector2D(100, 0),
	Vector2D(-50, 0),
	Vector2D(-100, 0),
};

Formation vFormation(v);
Formation iFormation(i);
Formation flatFormation(flat);
