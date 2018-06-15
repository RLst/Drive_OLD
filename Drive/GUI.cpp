#include "GUI.h"
#include <imgui.h>

GUI::GUI()
{
	startup();
}


GUI::~GUI()
{
}

void GUI::startup()
{
	//Startup IMGUI?
}

void GUI::draw()
{
	ImGui::Begin("Info");
	//ImGui::Text("FPS: %d", getFPS());
	//ImGui::Text("Score: %d", m_score);
	//ImGui::Text("HiScore: %d", m_hiscore);
	//ImGui::Text("Deaths: %d", m_deaths);
	ImGui::End();
}
