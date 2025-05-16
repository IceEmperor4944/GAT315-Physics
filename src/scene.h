#pragma once
#include "raylib.h"
#include "scene_camera.h"
#include <string>

class Scene
{
public:
	Scene(const std::string& title, int width, int height, const Color& background = BLACK);
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;

	virtual void BeginDraw();
	virtual void EndDraw();
	virtual void Draw() = 0;
	virtual void DrawGUI() = 0;

	bool IsQuit() { return WindowShouldClose(); }

	void SetCamera(SceneCamera* camera) { m_camera = camera; }
	SceneCamera* GetCamera() { return m_camera; }

	static constexpr float fixedTimestep = 1.0f / 60.0f;

	friend struct Body;
protected:
	void DrawGrid(float slices, float thickness, const Color& color);
	void DrawText(const std::string& text, const Vector2& world, int fontSize, const Color& color) const;
	void DrawCircle(const Vector2& world, float radius, const Color& color) const;
	void DrawLine(const Vector2& v1, const Vector2& v2, float thickness, const Color& color) const;
protected:
	int m_width{ 0 };
	int m_height{ 0 };
	Color m_background{ WHITE };

	SceneCamera* m_camera{ nullptr };
	class World* m_world{ nullptr };
};