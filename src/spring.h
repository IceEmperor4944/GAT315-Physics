#pragma once
#include "scene.h"
#include "body.h"
#include "raylib.h"

struct Spring {
public:
	Body* bodyA;
	Body* bodyB;
	float restLength;
	float k; // stiffness
	float damping;
public:
	Spring() = default;
	Spring(Body* bodyA, Body* bodyB, float restLength, float k, float damping = 0) :
		bodyA{ bodyA },
		bodyB{ bodyB },
		restLength{ restLength },
		k{ k },
		damping{ damping }
	{}

	void ApplyForce(float kMultiplier = 1);
	static void ApplyForce(const Vector2& position, Body& body, float restLength, float k, Body::ForceMode mode = Body::ForceMode::Force);
	void Draw(const Scene& scene);

	friend class Scene;
};