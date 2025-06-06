#pragma once
#include "scene.h"
#include "aabb.h"

struct Body {
public:
	enum class Type {
		Dynamic,
		Kinematic,
		Static
	};

	enum class ForceMode {
		Force,
		Impulse,
		Velocity
	};
	enum class Shape {
		Circle,
		Rectangle
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

	Body(Type type, Shape shape, const Vector2& position, float mass, float size, const Color& color) :
		type{ type },
		shape{ shape },
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
		invMass = (type == Type::Dynamic && mass != 0) ? 1 / mass : 0;
	}

	/*Body(Type type, const Vector2& cornerA, const Vector2& cornerB, float mass, const Color& color) :
		type{ type },
		cornerA{ cornerA },
		cornerB{ cornerB },
		mass{ mass },
		color{ color }
	{
		invMass = (type == Type::Dynamic && mass != 0) ? 1 / mass : 0;
		shape = Shape::Rectangle;
		position = { (cornerA.x + cornerB.x) / 2, (cornerA.y + cornerB.y) / 2 };
	}*/

	void Step(float dt);
	void Draw(const Scene& scene);

	void ApplyForce(const Vector2& force, ForceMode forceMode = ForceMode::Force);
	void ClearForce() { force = { 0, 0 }; }

	AABB GetAABB() const { return AABB{ position, { size * 2, size * 2 } }; }
public:
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	Vector2 force{ 0, 0 };

	bool hit = false;

	float mass{ 1 };
	float invMass{ 1 };

	float gravityScale{ 1 };
	float restitution{ 1 };

	float size = 1;
	float damping = 0.5f;
	Color color = WHITE;

	Type type = Type::Dynamic;
	Shape shape = Shape::Circle;
};