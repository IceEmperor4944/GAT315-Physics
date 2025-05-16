#pragma once
#include "scene.h"

//#define TYPE1
//#define TYPE2
#define TYPE3

struct Body;

class VectorScene : public Scene {
public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background) {
		//
	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;
private:
	bool mouseOverGUI = false;

	Vector2 anchor01 = { 64, 64 };
	Vector2 anchor02 = { 112, 104 };

	bool physicsWindowBoxActive = true;

	float massSliderBarValue = 1.0f;
	float sizeSliderBarValue = 0.1f;
	float gravityScaleSliderBarValue = 1.0f;
	float dampingSliderBarValue = 0.0f;
	float restitutionSliderBarValue = 1.0f;
	bool bodyTypeDropdownBoxEditMode = false;
	int bodyTypeDropdownBoxActive = 0;
};