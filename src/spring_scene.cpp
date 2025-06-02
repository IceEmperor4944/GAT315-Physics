#include "spring_scene.h"
#include "gui.h"
#include "world.h"
#include "gravitation.h"
#include "math_util.h"
#include "raymath.h"
#include "raygui.h"
#include <iostream>

void SpringScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void SpringScene::Update() {
	float dt = GetFrameTime();
	GUI::Update();

	if (IsKeyPressed(KEY_SPACE)) World::simulate = !World::simulate;

	float theta = randf(0, 360);

	if (!GUI::mouseOverGUI) {
		//place body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL))) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)GUI::bodyTypeActive;
			std::cout << GUI::bodyTypeActive << std::endl;

			Color c = ColorFromHSV(randf(360), 1, 1);
			Body* body = m_world->CreateBody(type, position, GUI::massValue, GUI::sizeValue, c);
			body->gravityScale = GUI::gravityScaleValue;
			body->restitution = GUI::restitutionValue;
			body->damping = GUI::dampingValue;

			body->ApplyForce(randomOnUnitCircle() * 10, Body::ForceMode::Velocity);
		}

		//select body
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
		if (m_selectedBody) {
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL)) {
				if (m_selectedBody->type == Body::Type::Dynamic) {
					Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
					Spring::ApplyForce(position, *m_selectedBody, 0.2f, 15.0f);
				}
			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connectBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else {
				if (m_selectedBody && m_connectBody) {
					float distance = Vector2Distance(m_selectedBody->position, m_connectBody->position);
					m_world->CreateSpring(m_selectedBody, m_connectBody, distance, 20, 0.0f);
				}
				m_selectedBody = nullptr;
				m_connectBody = nullptr;
			}
		}
	}

	//apply forces

	//apply collision
	for (auto body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			float overlap = (worldAABB.min().x - aabb.min().x);
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = (worldAABB.max().x - aabb.max().x);
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
		}
	}

	if (GUI::resetPressed) m_world->DestroyAll();
}

void SpringScene::FixedUpdate() {
	//apply forces
	m_world->Step(Scene::fixedTimestep);
}

void SpringScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);
	if (m_selectedBody) {
		DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);
		if (m_connectBody) {
			DrawCircleLine(m_connectBody->position, m_connectBody->size, YELLOW, 5);
			DrawLine(m_selectedBody->position, m_connectBody->position, 3, GREEN);
		}
		else {
			DrawLine(m_selectedBody->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
	}

	m_camera->EndMode();
}

void SpringScene::DrawGUI() {
	GUI::Draw();
}