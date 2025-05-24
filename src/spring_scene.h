#pragma once
#include "scene.h"

//#define TYPE1
//#define TYPE2
#define TYPE3

struct Body;

class SpringScene : public Scene {
public:
	SpringScene(const std::string& title, int width, int height, const Color& background = BLACK) :
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
	Body* m_connectBody{ nullptr };
};