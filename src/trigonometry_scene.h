#pragma once
#include "scene.h"

class TrigonometryScene : public Scene {
public:
	TrigonometryScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background) {

	}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void DrawGUI() override;
private:

};