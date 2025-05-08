#pragma once
#include "scene.h"

struct Body;

class VectorScene : public Scene {
public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background) {
		//
	}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void DrawGUI() override;
private:
	Body* m_head{ nullptr };
	Body* m_player{ nullptr };
};