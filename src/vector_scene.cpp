#include "vector_scene.h"
#include "gui.h"
#include "world.h"
#include "gravitation.h"
#include "math_util.h"
#include "raymath.h"
#include "raygui.h"
#include <iostream>

void VectorScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void VectorScene::Update() {
	float dt = GetFrameTime();
	GUI::Update();

	float theta = randf(0, 360);

	if (!GUI::mouseOverGUI && IsMouseButtonPressed(0)) {
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		Body::Type type = (Body::Type)GUI::bodyTypeActive;
		std::cout << GUI::bodyTypeActive << std::endl;

		for (int i = 0; i < 100; i++) {
			Color c = ColorFromHSV(randf(360), 1, 1);
			Body* body = m_world->CreateBody(position, GUI::massValue, GUI::sizeValue, c);
			float offset = randf(0, 360);
			body->gravityScale = GUI::gravityScaleValue;
			body->restitution = GUI::restitutionValue;
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
			for (int j = 0; j < 6; j++) {
				Body* newBody = m_world->CreateBody(position, GUI::massValue, GUI::sizeValue, c);
				newBody->velocity = body->velocity;
				newBody->damping *= 1 + (GUI::sizeValue * j);
				newBody->gravityScale = body->gravityScale;
				newBody->restitution = body->restitution;
				newBody->mass = body->mass;
			}
#endif
		}
	}

	//apply forces


	//apply collision
	for (auto body : m_world->GetBodies()) {
		if (body->position.y < -5) {
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}
		if (body->position.x < -9) {
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}
		if (body->position.x > 9) {
			body->position.x = 9;
			body->velocity.x *= -body->restitution;
		}
	}
}

void VectorScene::FixedUpdate() {
	//apply forces
	m_world->Step(Scene::fixedTimestep);
}

void VectorScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI() {
	GUI::Draw();
}