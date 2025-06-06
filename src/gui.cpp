#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void GUI::Initialize()
{
	//GuiLoadStyle("../raygui/styles/jungle/style_dark.rgs");
	//GuiLoadStyle("../raygui/styles/terminal/style_terminal.rgs");
}

void GUI::Update()
{
	mouseOverGUI = physicsWindowBoxActive && CheckCollisionPointRec(GetMousePosition(), { anchor01.x + 0, anchor01.y + 0, 280, 504 });
	if (IsKeyPressed(KEY_TAB)) physicsWindowBoxActive = !physicsWindowBoxActive;
}

void GUI::Draw()
{
	if (bodyTypeEditMode) GuiLock();

	if (physicsWindowBoxActive)
	{
		physicsWindowBoxActive = !GuiWindowBox(Rectangle{ anchor01.x + 0, anchor01.y + 0, 312, 472 }, "Physics");
		GuiToggle(Rectangle{ anchor01.x + 24, anchor01.y + 432, 120, 24 }, "Simulate", &World::simulate);
		resetPressed = GuiButton(Rectangle{ anchor01.x + 168, anchor01.y + 432, 120, 24 }, "Reset");

		GuiGroupBox(Rectangle{ anchor02.x + 0, anchor02.y + 0, 256, 184 }, "Body");
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 16, 120, 16 }, "Mass", GUI_DATA(massValue), 0, 10);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 40, 120, 16 }, "Size", GUI_DATA(sizeValue), 0.1f, 1.0f);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 64, 120, 16 }, "Gravity Scale", GUI_DATA(gravityScaleValue), 0, 10);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 88, 120, 16 }, "Damping", GUI_DATA(dampingValue), 0, 5);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 112, 120, 16 }, "Restitution", GUI_DATA(restitutionValue), 0, 2);
		GuiLabel(Rectangle{ anchor02.x + 24, anchor02.y + 136, 120, 24 }, "Body Type");
		GuiGroupBox(Rectangle{ anchor03.x + 0, anchor03.y + 8, 256, 72 }, "Spring");
		GuiSliderBar(Rectangle{ anchor03.x + 96, anchor03.y + 24, 120, 16 }, "Damping", GUI_DATA(springDampingValue), 0, 10);
		GuiSliderBar(Rectangle{ anchor03.x + 96, anchor03.y + 48, 120, 16 }, "Stiffness", GUI_DATA(stiffnessValue), 0, 20);
		GuiGroupBox(Rectangle{ anchor04.x + 0, anchor04.y + -8, 264, 96 }, "World");
		GuiSliderBar(Rectangle{ anchor03.x + 96, anchor03.y + 104, 120, 16 }, "Gravitation", GUI_DATA(World::gravitation), 0, 100);
		GuiSlider(Rectangle{ anchor04.x + 96, anchor04.y + 56, 120, 16 }, "Gravity", GUI_DATA(World::gravity.y), -20, 20);
		GuiSliderBar(Rectangle{ anchor03.x + 96, anchor03.y + 128, 120, 16 }, "Spring Multiplier", GUI_DATA(World::springStiffnessMultiplier), 0, 10);
		if (GuiDropdownBox(Rectangle{ anchor02.x + 96, anchor02.y + 136, 120, 24 }, "Dynamic;Kinematic;Static", &bodyTypeActive, bodyTypeEditMode)) bodyTypeEditMode = !bodyTypeEditMode;
	}

	GuiUnlock();
}

void GUI::DrawGame() {
	guiFont.baseSize = 6;
	physicsWindowBoxActive = !GuiWindowBox(Rectangle{ anchor01.x + 0, anchor01.y + 0, 312, 150 }, "Physics");
	GuiGroupBox(Rectangle{ anchor02.x + 0, anchor02.y + 0, 256, 90 }, "Stack & Crack");
	GuiValueBox(Rectangle{ anchor02.x + 96, anchor02.y + 20, 120, 24 }, "Score: ", score, 0, maxScore, false);
	GuiValueBox(Rectangle{ anchor02.x + 96, anchor02.y + 50, 120, 24 }, "Balls Left: ", ballsLeft, 0, maxBalls, false);

	if (hasWon) {
		GuiPanel(Rectangle{ anchor05.x, anchor05.y, 200, 180 }, "Game Over");
		guiFont.baseSize = 3;
		GuiLabel(Rectangle{ anchor05.x + 40, anchor05.y + 20, 120, 60 }, "You Win");
		guiFont.baseSize = 6;
		resetPressed = GuiButton(Rectangle{ anchor05.x + 40, anchor05.y + 100, 120, 60 }, "Restart");
		if (resetPressed) hasWon = false;
	}
	if (hasLost) {
		GuiPanel(Rectangle{ anchor05.x, anchor05.y, 200, 180 }, "Game Over");
		guiFont.baseSize = 3;
		GuiLabel(Rectangle{ anchor05.x + 36, anchor05.y + 20, 140, 60 }, "You Lose");
		guiFont.baseSize = 6;
		resetPressed = GuiButton(Rectangle{ anchor05.x + 40, anchor05.y + 100, 120, 60 }, "Restart");
		if (resetPressed) hasLost = false;
	}
}

Body* GUI::GetBodyIntersect(const Vector2& position, bodies_t& bodies, const SceneCamera& camera)
{
	for (auto body : bodies)
	{
		if (CheckCollisionPointCircle(position, body->position, body->size))
		{
			return body;
		}
	}

	return nullptr;
}