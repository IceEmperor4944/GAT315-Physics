#pragma once
#include "raylib.h"
#include<vector>

struct Body;

class World {
public: 
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	void Step(float timestep);
	void Draw(const class Scene& scene);

	void DestroyAll();

	static Vector2 gravity;
private:
	std::vector<Body*> m_bodies;
};