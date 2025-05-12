#include "vector_scene.h"
#include "body.h"
#include "math_util.h"
#include "raymath.h"

void VectorScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void VectorScene::Update() {
	float dt = GetFrameTime();

	float theta = randf(0, 360);

	if (IsMouseButtonPressed(0)) {
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0; i < 100; i++) {
			Color c = ColorFromHSV(randf(360), 1, 1);
			Body* body = m_world->CreateBody(position, 0.05f, c);
			float offset = randf(0, 360);
#ifdef TYPE1
			float x = cosf(theta * offset);
			float y = sinf(theta * offset);
			body->velocity = Vector2{ x, y } *randf(1, 6);
#elif defined TYPE2
			float x = cosf(theta);
			float y = sinf(theta);
			body->velocity = Vector2{ y, x } *randf(1, 6);
#elif defined TYPE3
			float x = cosf(theta * offset);
			float y = sinf(theta * offset);
			body->velocity = Vector2{ x, y } *randf(1, 6);
			for (int j = 0; j < 30; j++) {
				Body* newBody = m_world->CreateBody(position, 0.05f, c);
				newBody->velocity = body->velocity;
				newBody->damping *= 1 + (0.05f * j);
			}
#endif
		}
	}

	m_world->Step(dt);
}

void VectorScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI() {

}