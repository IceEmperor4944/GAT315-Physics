#include "polar_scene.h"

void PolarScene::Initialize() {
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void PolarScene::Update() {

}

void PolarScene::FixedUpdate()
{

}

void PolarScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);

#ifdef ARCHIMEDIAN
	int steps = 200;
	float time = (float)GetTime();
	float a = 0;
	float b = 0.35f;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps) * 8 * PI;
		float r = a + (b * theta);

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, GREEN);
	}
#elif defined CARDIOID
	int steps = 200;
	float time = (float)GetTime();
	float a = 2.5f;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps) * 8 * PI;
		float r = a * (1 + cosf(theta));

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, GREEN);
	}
#elif defined LIMACON
	int steps = 200;
	float time = (float)GetTime();
	float a = 1.5f;
	float b = 3.5f;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps) * 8 * PI;
		float r = a + (b * cosf(theta));

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, GREEN);
	}
#elif defined ROSE
	int steps = 500;
	float time = (float)GetTime();
	float a = 4.5f;
	float k = 5.0f;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps) * 8 * PI;
		//float r = a * (cosf(k * theta));
		float r = a * (sinf(k * theta));

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, GREEN);
	}
#elif defined USER
	int steps = 500;
	float time = (float)GetTime();
	float a = 3.5f;
	float b = 1.5f;
	float k = 6.5f;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps) * 8 * PI;
		float r = a + (b * cosf(k * theta));

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, GREEN);
	}
#endif

	m_camera->EndMode();
}

void PolarScene::DrawGUI() {

}