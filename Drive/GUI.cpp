#include "GUI.h"
#include <imgui.h>

GUI::GUI(Car* car)
{
	startup(Car* car);
}

GUI::~GUI()
{}

void GUI::startup(Car* car)
{
	//Startup IMGUI?
	m_subject = car;
}

//void GUI::update(float deltaTime)
//{
//	m_carObserving = onNotify()
//}

void GUI::onNotify(Car & car)
{
	m_carObserved = car;
}

Car & GUI::getMutable(Car * car)
{
	m_subject = car;
}

void GUI::draw(/*aie::Renderer2D * renderer*/)
{
	ImGui::Begin("Info");
	ImGui::Text("");
	//ImGui::Text("FPS: %d", getFPS());
	//ImGui::Text("Score: %d", m_score);
	//ImGui::Text("HiScore: %d", m_hiscore);
	//ImGui::Text("Deaths: %d", m_deaths);
	ImGui::End();
}
