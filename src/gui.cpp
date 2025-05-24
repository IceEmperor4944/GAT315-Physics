#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void GUI::Initialize()
{
	GuiLoadStyle("../raygui/styles/jungle/style_jungle.rgs");
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
		physicsWindowBoxActive = !GuiWindowBox(Rectangle{ anchor01.x + 0, anchor01.y + 0, 312, 464 }, "Physics");
		GuiToggle(Rectangle{ anchor01.x + 96, anchor01.y + 424, 120, 24 }, "Simulate", &World::simulate);

		GuiGroupBox(Rectangle{ anchor02.x + 0, anchor02.y + 0, 256, 184 }, "Body");
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 16, 120, 16 }, "Mass", GUI_DATA(massValue), 0, 10);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 40, 120, 16 }, "Size", GUI_DATA(sizeValue), 0.1f, 10.0f);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 64, 120, 16 }, "Gravity Scale", GUI_DATA(gravityScaleValue), 0, 10);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 88, 120, 16 }, "Damping", GUI_DATA(dampingValue), 0, 5);
		GuiSliderBar(Rectangle{ anchor02.x + 96, anchor02.y + 112, 120, 16 }, "Restitution", GUI_DATA(restitutionValue), 0, 2);
		GuiLabel(Rectangle{ anchor02.x + 24, anchor02.y + 136, 120, 24 }, "Body Type");
		GuiGroupBox(Rectangle{ anchor03.x + 0, anchor03.y + 8, 256, 72 }, "Spring");
		GuiSliderBar(Rectangle{ anchor03.x + 96, anchor03.y + 24, 120, 16 }, "Damping", GUI_DATA(springDampingValue), 0, 10);
		GuiSliderBar(Rectangle{ anchor03.x + 96, anchor03.y + 48, 120, 16 }, "Stiffness", GUI_DATA(stiffnessValue), 0, 20);
		GuiGroupBox(Rectangle{ anchor04.x + 0, anchor04.y + 0, 256, 72 }, "World");
		GuiSliderBar(Rectangle{ anchor03.x + 96, anchor03.y + 112, 120, 16 }, "Gravitation", GUI_DATA(World::gravitation), 0, 100);
		GuiSlider(Rectangle{ anchor04.x + 96, anchor04.y + 40, 120, 16 }, "Gravity", GUI_DATA(World::gravity.y), -20, 20);
		if (GuiDropdownBox(Rectangle{ anchor02.x + 96, anchor02.y + 136, 120, 24 }, "Dynamic;Kinematic;Static", &bodyTypeActive, bodyTypeEditMode)) bodyTypeEditMode = !bodyTypeEditMode;
	}

	GuiUnlock();
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