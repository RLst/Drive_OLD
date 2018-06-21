#include "GUI.h"
#include <imgui.h>
#include "Car.h"

//GUI::GUI()
//{
//}
//
////GUI::GUI(Car* car)
////{
////	//startup(Car* car);
////}
//
//GUI::~GUI()
//{}

//void GUI::startup(Car* car)
//{
//	//Startup IMGUI?
//	m_subject = car;
//}

//void GUI::update(float deltaTime)
//{
//	m_carObserving = onNotify()
//}

//void GUI::onNotify(Car & car)
//{
//	m_carObserved = car;
//}
//
//Car & GUI::getMutable(Car * car)
//{
//	m_subject = car;
//}

void GUI::draw(Car * car)
{
	ImGui::Begin("Car");
	ImGui::Text("RPM: %d", (int)car->calcNewRPM());
	ImGui::Text("Velocity: %d", (int)car->getVelocity());
	ImGui::End();
}
