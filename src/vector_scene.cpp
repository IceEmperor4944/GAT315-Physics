#include "vector_scene.h"
#include "world.h"
#include "gravitation.h"
#include "math_util.h"
#include "raymath.h"
#include "raygui.h"
#include <iostream>

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void VectorScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void VectorScene::Update() {
	float dt = GetFrameTime();

	float theta = randf(0, 360);

	if (!mouseOverGUI && IsMouseButtonPressed(0)) {
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		Body::Type type = (Body::Type)bodyTypeDropdownBoxActive;
		std::cout << bodyTypeDropdownBoxActive << std::endl;

		for (int i = 0; i < 100; i++) {
			Color c = ColorFromHSV(randf(360), 1, 1);
			Body* body = m_world->CreateBody(position, sizeSliderBarValue, c);
			float offset = randf(0, 360);
			body->gravityScale = gravityScaleSliderBarValue;
			body->restitution = restitutionSliderBarValue;
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
				Body* newBody = m_world->CreateBody(position, sizeSliderBarValue, c);
				newBody->velocity = body->velocity;
				newBody->damping *= 1 + (sizeSliderBarValue * j);
				newBody->gravityScale = body->gravityScale;
				newBody->restitution = body->restitution;
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
	ApplyGravitation(m_world->GetBodies(), 1);
	m_world->Step(Scene::fixedTimestep);
}

void VectorScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI() {
	mouseOverGUI = physicsWindowBoxActive && CheckCollisionPointRec(GetMousePosition(), { anchor01.x + 0, anchor01.y + 0, 280, 488 });

	if (bodyTypeDropdownBoxEditMode) GuiLock();

	if (physicsWindowBoxActive) {
		physicsWindowBoxActive = !GuiWindowBox(Rectangle{ anchor01.x + 0, anchor01.y + 0, 280, 488 }, "PHYSICS");
		GuiSlider(Rectangle{ anchor01.x + 112, anchor01.y + 432, 120, 16 }, "WORLD GRAVITY", NULL, &World::gravity.y, -20, 20);
		if (GuiDropdownBox(Rectangle{ anchor01.x + 24, anchor01.y + 264, 120, 24 }, "DYNAMIC; KINEMATIC; STATIC", &bodyTypeDropdownBoxActive, bodyTypeDropdownBoxEditMode)) bodyTypeDropdownBoxEditMode = !bodyTypeDropdownBoxEditMode;
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 24, 120, 16 }, "MASS", GUI_DATA(massSliderBarValue), 0, 10);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 56, 120, 16 }, "SIZE", GUI_DATA(sizeSliderBarValue), 0.1f, 5.0f);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 88, 120, 16 }, "GRAVITY SCALE", GUI_DATA(gravityScaleSliderBarValue), 0, 5);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 120, 120, 16 }, "DAMPING", NULL, &dampingSliderBarValue, 0, 1);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 152, 120, 16 }, "RESTITUTION", NULL, &restitutionSliderBarValue, 0, 1);
		GuiGroupBox(Rectangle{ anchor02.x - 32, anchor02.y + 8, 248, 192 }, "BODY");
	}

	GuiUnlock();
}