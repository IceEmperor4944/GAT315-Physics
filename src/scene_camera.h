#pragma once
#include "raylib.h"

class SceneCamera
{
public:
	SceneCamera(const Vector2& offset, const Vector2& target = Vector2{ 0, 0 }, float rotation = 0, float size = 5) :
		m_size{ size }
	{
		m_camera.offset = offset;
		m_camera.target = target;
		m_camera.rotation = rotation;
		m_camera.zoom = offset.y / (size * m_ppu);
	}

	void BeginMode();
	void EndMode();

	Camera2D& GetCamera() { return m_camera; }

	void SetSize(float size) { m_size = size; }
	float GetSize() const { return m_size; }

	void SetPPU(float ppu) { m_ppu = ppu; }
	float GetPPU() const { return m_ppu; }

	float ScreenToWorld(float screen) const { return screen / m_ppu; }
	float WorldToScreen(float world) const { return world * m_ppu; }

	Vector2 ScreenToWorld(const Vector2& screen);
	Vector2 WorldToScreen(const Vector2& world);

private:
	Camera2D m_camera;

	float m_size{ 0 };	// half vertical number of units
	float m_ppu{ 100 }; // pixels per unit
};
