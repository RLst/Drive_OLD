#include "GUI.h"
#include <imgui.h>
#include "Car.h"

void GUI::draw(Car * car)
{
	ImGui::Begin("Car");
	ImGui::Text("RPM: %d", (int)car->calcNewRPM());
	ImGui::Text("Velocity: %d", (int)car->getVelocity());
	ImGui::End();

	//std::cout << "Gear: " << m_current_gear << std::endl;
	//std::cout << "RPM: " << calcNewRPM() << std::endl;
	//std::cout << "Wheel force: " << ForceWheel().magnitude() << std::endl;
	//std::cout << "Brake force: " << ForceBraking().magnitude() << std::endl;
}
