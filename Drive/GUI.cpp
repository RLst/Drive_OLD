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

void GUI::update(float deltaTime)
{
	m_carObserved = onNotify()
}

void GUI::onNotify(Car & car)
{
	m_carObserved = car;
}

void GUI::draw(/*aie::Renderer2D * renderer*/)
{
	ImGui::Begin("Info");
	ImGui::Text("")
	//ImGui::Text("FPS: %d", getFPS());
	//ImGui::Text("Score: %d", m_score);
	//ImGui::Text("HiScore: %d", m_hiscore);
	//ImGui::Text("Deaths: %d", m_deaths);
	ImGui::End();
}
