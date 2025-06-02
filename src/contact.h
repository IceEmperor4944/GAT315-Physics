#pragma once
#include "raylib.h"

struct Contact
{
	struct Body* bodyA;
	struct Body* bodyB;

	float restitution;	// restitution of both bodies
	float depth;		// penetration depth
	Vector2 normal;		// normal contact vector
};