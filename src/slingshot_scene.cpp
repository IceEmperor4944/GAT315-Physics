#include "slingshot_scene.h"
#include "gui.h"
#include "world.h"
#include "gravitation.h"
#include "math_util.h"
#include "raymath.h"
#include "raygui.h"
#include <iostream>

void SlingshotScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void SlingshotScene::Update() {
	float dt = GetFrameTime();
	GUI::Update();

	if (IsKeyPressed(KEY_SPACE)) World::simulate = !World::simulate;

	float theta = randf(0, 360);

	if (!GUI::mouseOverGUI) {
		//place body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_CONTROL)) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)GUI::bodyTypeActive;

			Color c = ColorFromHSV(randf(360), 1, 1);
			Body* body = m_world->CreateBody(type, Body::Shape::Circle, position, GUI::massValue, GUI::sizeValue, c);
			body->gravityScale = 0.0f;
			body->restitution = GUI::restitutionValue;
			body->damping = GUI::dampingValue * 3.0f;
			GUI::ballsNum--;

			//body->ApplyForce(randomOnUnitCircle() * 10, Body::ForceMode::Velocity);
		}
		else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL))) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)GUI::bodyTypeActive;

			Color c = ColorFromHSV(randf(360), 1, 1);
			Body* body = m_world->CreateBody(type, Body::Shape::Rectangle, position, GUI::massValue, GUI::sizeValue * 5, c);
			body->gravityScale = 1.0f;
			body->restitution = 0.0f;
			body->damping = 1.0f;
			GUI::maxScore += 100;
		}

		//select body
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
		if (m_selectedBody) {
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				//m_connectBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_selectedBody->gravityScale = GUI::gravityScaleValue;
				Spring::ApplyForce(m_selectedBody->position - position, *m_selectedBody, 0.2f, 10.0f, Body::ForceMode::Impulse);
			}
			else {
				//if (m_selectedBody && m_connectBody) {
				//	float distance = Vector2Distance(m_selectedBody->position, m_connectBody->position);
				//	m_world->CreateSpring(m_selectedBody, m_connectBody, distance, GUI::stiffnessValue, GUI::springDampingValue);
				//}
				m_selectedBody = nullptr;
				//m_connectBody = nullptr;
			}
		}
	}

	//int bodiesHit = 0;
	//apply collision
	for (auto body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 1 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 1 * overlap; // move the body back inside the world bounds
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

		/*if (body->hit && body->shape == Body::Shape::Rectangle) {
			bodiesHit++;
			GUI::scoreVal = bodiesHit * 100;
		}*/
	}

	//if (GUI::scoreVal == GUI::maxScore && m_world->GetBodies().size() != 0) GUI::hasWon = true;
	//if (GUI::ballsNum == 0 && GUI::scoreVal != GUI::maxScore) GUI::hasLost = true;

	if (GUI::resetPressed) m_world->DestroyAll();
}

void SlingshotScene::FixedUpdate() {
	//apply forces
	m_world->Step(Scene::fixedTimestep);
}

void SlingshotScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);
	/*if (m_startLocation != Vector2Zero()) {
		DrawRectangleLines(m_startLocation.x + m_camera->ScreenToWorld(GetMousePosition()).x,
			m_startLocation.y + m_camera->ScreenToWorld(GetMousePosition()).y,
			m_camera->ScreenToWorld(GetMousePosition()).x - m_startLocation.x,
			m_camera->ScreenToWorld(GetMousePosition()).y - m_startLocation.y,
			WHITE);
	}*/
	if (m_selectedBody) {
		DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);
		DrawLine(m_selectedBody->position, m_camera->ScreenToWorld(GetMousePosition()), 3, WHITE);
	}

	m_camera->EndMode();
}

void SlingshotScene::DrawGUI() {
	GUI::DrawGame();
}