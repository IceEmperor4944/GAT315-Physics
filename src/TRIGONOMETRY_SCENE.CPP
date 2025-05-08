#include "trigonometry_scene.h"

void TrigonometryScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void TrigonometryScene::Update() {

}

//this and next are also in raylib, so not necessary if include raymath.h
float Vector2Length(const Vector2& v) {
	return sqrtf((v.x * v.x) + (v.y * v.y));
}

Vector2 Vector2Normalize(const Vector2& v) {
	float l = Vector2Length(v);
	return l == 0 ? Vector2{ 0, 0 } : Vector2{ v.x / l, v.y / l }; //I LOVE TERNARIES RAAAAAAAAAAA
}

void TrigonometryScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	//DrawCircle(Vector2{ 0, 0 }, 1, DARKPURPLE);
	
	float radius = 3;
	float rate = 2.0f;
	float time = (float)GetTime() * rate;

	int steps = 50;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps) * (2 * PI); //0 - 1
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;
	
		DrawCircle(Vector2{ x, y }, 0.25f, RED);
	}

	// sin / cos
	for (float x = -9.0f; x < 9; x += 0.2f) {
		float theta = time + ((x / 18) * (2 * PI)); //0 - 1
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;

		DrawCircle(Vector2{ x, c }, 0.25f, GREEN);
		DrawCircle(Vector2{ x, s }, 0.25f, BLUE);
	}

	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{ x, y }, 0.3f, YELLOW); //tracks circle
	DrawCircle(Vector2{ 0, y }, 0.3f, ORANGE); //tracks sin value
	DrawCircle(Vector2{ 0, x }, 0.3f, PINK);   //tracks cos value

	float angle = (float)atan2(y, x); //gives angle between these two coordinates, have to put target first then start

	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI() {

}