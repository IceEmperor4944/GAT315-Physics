#pragma once
#include "scene.h"
#include "raylib.h"

struct Body {
public:
	Body() = default;
	Body(const Vector2& position, const Vector2& velocity, float size, const Color& color):
		position{position},
		velocity{velocity},
		size{size},
		color{color}
	{ }

	void Step(float dt);
	void Draw(const Scene& scene);
public:
	Vector2 position;
	Vector2 velocity;

	float size;
	Color color;

	Body* next{ nullptr };
	Body* prev{ nullptr };
};