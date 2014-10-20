#pragma once
#include <math.h>

class Vector2D
{
	
public:
	float x, y;
	Vector2D(float x, float y) :x(x), y(y){ } 
	Vector2D() :x(0), y(0){ }
	~Vector2D();
	Vector2D operator+(Vector2D const& r)
	{
		return Vector2D(x + r.x, y + r.y);
	}
	Vector2D operator+=(Vector2D const& r)
	{
		x += r.x;
		y += r.y;
		return *this;
	}
	Vector2D operator-(Vector2D const& r)
	{
		return Vector2D(x - r.x, y - r.y);
	}
	Vector2D operator*(float f)
	{
		return Vector2D(x * f, y * f);
	}
	Vector2D operator/(float f)
	{
		return Vector2D(x / f, y / f);
	}
	float DistanceSquared()
	{
		return x*x + y*y;
	}
	float Distance()
	{
		return sqrt(DistanceSquared());
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	
};

