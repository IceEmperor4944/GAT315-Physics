#pragma once
#include "scene.h"
#include "raylib.h"

struct Body {
public:
	enum class Type {
		Dynamic,
		Kinematic,
		Static
	};
public:
	Body() = default;
	Body(const Vector2& position, const Vector2& velocity, float mass, float size, const Color& color) :
		position{ position },
		velocity{ velocity },
		mass{ mass },
		size{ size },
		color{ color }
	{
	}

	Body(const Vector2& position, float mass, float size, const Color& color) :
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
	}

	Body(Type type, const Vector2& position, float mass, float size, const Color& color) :
		type{ type },
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
		invMass = (type == Type::Dynamic && mass != 0) ? 1 / mass : 0;
	}

	void Step(float dt);
	void Draw(const Scene& scene);

	void ApplyForce(const Vector2& force);
	void ClearForce() { force = { 0, 0 }; }
public:
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	Vector2 force{ 0, 0 };

	float mass{ 1 };
	float invMass{ 1 };

	float gravityScale{ 1 };
	float restitution{ 1 };

	float size = 1;
	float damping = 0.5f;
	Color color = WHITE;

	Type type = Type::Dynamic;

	Body* next{ nullptr };
	Body* prev{ nullptr };
};