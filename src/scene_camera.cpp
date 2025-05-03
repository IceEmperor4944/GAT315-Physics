#include "scene_camera.h"
#include "rlgl.h"

void SceneCamera::BeginMode()
{
	m_camera.zoom = m_camera.offset.y / (m_size * m_ppu);

	rlDisableBackfaceCulling();
	rlPushMatrix();

	// translate to camera offset (screen center)
	rlTranslatef(m_camera.offset.x, m_camera.offset.y, 0.0f);
	// apply zoom
	rlScalef(m_camera.zoom, -m_camera.zoom, 1.0f); // note: negative Y for flip
	// apply rotation
	rlRotatef(m_camera.rotation, 0.0f, 0.0f, 1.0f);
	// translate to negative camera target
	rlTranslatef(-m_camera.target.x, -m_camera.target.y, 0.0f);
}

void SceneCamera::EndMode()
{
	rlPopMatrix();
}

Vector2 SceneCamera::ScreenToWorld(const Vector2& screen)
{
	// convert to centered coordinates
	float screenX = screen.x - m_camera.offset.x;
	float screenY = screen.y - m_camera.offset.y;

	// convert to world, flip y
	float worldX = screenX / (m_camera.zoom * m_ppu) + m_camera.target.x;
	float worldY = -screenY / (m_camera.zoom * m_ppu) + m_camera.target.y;

	return { worldX, worldY };
}

Vector2 SceneCamera::WorldToScreen(const Vector2& world)
{
	return { world.x * m_ppu, world.y * m_ppu };
}