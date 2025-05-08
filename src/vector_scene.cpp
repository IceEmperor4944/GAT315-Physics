#include "vector_scene.h"
#include "body.h"
#include "math_util.h"
#include "raymath.h"

void VectorScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	Body* body = new Body(Vector2{ 3, 0 }, Vector2{ 0, 0 }, 0.25f, WHITE);
	m_head = body;
	m_player = body;

	//creates 10 objects at random locations
	//links them together in list
	for (int i = 0; i < 10; i++) {
		body->next = new Body(Vector2{ randf(10), randf(5) }, Vector2{ 0, 0 }, 0.25f, RED);
		body->next->prev = body;
		body = body->next;
	}
}

void VectorScene::Update() {
	float dt = GetFrameTime();

	//player control
	Vector2 input{ 0, 0 };
	if (IsKeyDown(KEY_A)) input.x = -1;
	if (IsKeyDown(KEY_D)) input.x =  1;
	if (IsKeyDown(KEY_W)) input.y =  1;
	if (IsKeyDown(KEY_S)) input.y = -1;
	input = Vector2Normalize(input);
	m_player->velocity = input * 3;

	Body* body = m_head;
	while (body) {
		if (body == m_player) {
			body->Step(dt);
			body = body->next;
			continue;
		}

		Vector2 direction = m_player->position - body->position;
		direction = Vector2Normalize(direction) * 1;
		body->velocity = direction;

		body->Step(dt);
		body = body->next;
	}
}

void VectorScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);

	Body* body = m_head;
	while (body) {
		body->Draw(*this);
		body = body->next;
	}

	m_camera->EndMode();
}

void VectorScene::DrawGUI() {

}