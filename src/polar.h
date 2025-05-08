#pragma once
#include "raylib.h"
#include "raymath.h"

struct Polar
{
public:
	Polar() = default;
	Polar(float angle, float radius) :
		angle{ angle },
		radius{ radius }
	{
	}

	Polar(const Vector2& v) :
		angle{ atan2f(v.y, v.x) },
		radius{ Vector2Length(v) }
	{
	}

	Polar& operator = (const Vector2& v)
	{
		angle = atan2f(v.y, v.x);
		radius = Vector2Length(v);

		return *this;
	}

	operator Vector2() const
	{
		Vector2 v;
		v.x = cosf(angle) * radius;
		v.y = sinf(angle) * radius;

		return v;
	}

public:
	float angle{ 0 };
	float radius{ 0 };
};