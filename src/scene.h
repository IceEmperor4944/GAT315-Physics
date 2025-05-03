#pragma once
#include "raylib.h"
//#include "gui.h"
#include "scene_camera.h"
#include <string>

class Scene
{
public:
	Scene(const std::string& title, int width, int height, const Color& background = BLACK);
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update() = 0;

	virtual void BeginDraw();
	virtual void EndDraw();
	virtual void Draw() = 0;
	virtual void DrawGUI() = 0;

	bool IsQuit() { return WindowShouldClose(); }

	void SetCamera(SceneCamera* camera) { m_camera = camera; }
	SceneCamera* GetCamera() { return m_camera; }

protected:
	void DrawGrid(float slices, float thickness, const Color& color);

protected:
	int m_width{ 0 };
	int m_height{ 0 };
	Color m_background{ WHITE };

	SceneCamera* m_camera{ nullptr };
};