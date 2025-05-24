#pragma once
#include "world.h"
#include "raylib.h"

class GUI {
public:
	static void Initialize();
	static void Update();
	static void Draw();

	static struct Body* GetBodyIntersect(const Vector2& position, bodies_t& bodies, const SceneCamera& camera);
public:
	inline static bool mouseOverGUI = false;

	inline static Vector2 anchor01 = { 72, 48 };
	inline static Vector2 anchor02 = { 96, 88 };
	inline static Vector2 anchor03 = { 96, 288 };
	inline static Vector2 anchor04 = { 96, 384 };
	
	inline static bool physicsWindowBoxActive = true;
	
	inline static float massValue = 1.0f;
	inline static float sizeValue = 0.1f;
	inline static float gravityScaleValue = 1.0f;
	inline static float dampingValue = 0.0f;
	inline static float restitutionValue = 1.0f;
	inline static bool bodyTypeEditMode = false;
	inline static int bodyTypeActive = 0;
	inline static float springDampingValue = 0.5f;
	inline static float stiffnessValue = 15.0f;
	inline static float gravitationValue = 0.0f;
	inline static float gravityValue = 0.0f;
	inline static bool simulateActive = true;
};