#include "scene.h"
#include "rlgl.h"

Scene::Scene(const std::string& title, int width, int height, const Color& background) :
	m_width{ width },
	m_height{ height },
	m_background{ background }
{
	InitWindow(width, height, title.c_str());
}

Scene::~Scene()
{
	CloseWindow();
}

void Scene::BeginDraw()
{
	BeginDrawing();
	ClearBackground(m_background);
}

void Scene::EndDraw()
{
	EndDrawing();
}

void Scene::DrawGrid(float slices, float thickness, const Color& color)
{
	for (float i = -slices; i <= slices; i++)
	{
		DrawLineEx(m_camera->WorldToScreen(Vector2{ -slices, i }), m_camera->WorldToScreen(Vector2{ slices, i }), thickness, color);
		DrawLineEx(m_camera->WorldToScreen(Vector2{ i, -slices }), m_camera->WorldToScreen(Vector2{ i, slices }), thickness, color);
	}
}

void Scene::DrawText(const std::string& text, const Vector2& world, int fontSize, const Color& color) const {
	Vector2 screen = m_camera->WorldToScreen(world);

	rlPushMatrix();
	rlTranslatef(screen.x, screen.y, 0);
	rlScalef(1, -1, 1);  // flip back so text is upright
	::DrawText(text.c_str(), 0, 0, fontSize, color); //:: calls global
	rlPopMatrix();
}

void Scene::DrawCircle(const Vector2& world, float radius, const Color& color) const {
	DrawCircleV(m_camera->WorldToScreen(world), m_camera->WorldToScreen(radius), color);
}

void Scene::DrawLine(const Vector2& v1, const Vector2& v2, float thickness, const Color& color) const {
	DrawLineEx(m_camera->WorldToScreen(v1), m_camera->WorldToScreen(v2), thickness, color);
}