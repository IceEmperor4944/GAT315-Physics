#pragma once
#include "scene.h"

struct Body;

class SlingshotScene : public Scene {
public:
	SlingshotScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background) {
		//
	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;
private:
	Body* m_selectedBody{ nullptr };
	Vector2 m_startLocation{ 0, 0 };

	float destroyCount = 0;
};