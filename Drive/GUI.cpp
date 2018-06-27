#include "GUI.h"
#include <imgui.h>
#include "Car.h"

void GUI::draw(Car * car)
{
	ImGui::Begin("Car");
	ImGui::Text("Gear: %s", car->getGEARstr());
	ImGui::Text("RPM: %d", (int)car->getRPM());
	ImGui::Text("Velocity: %d", (int)car->getVelocity());				//World velocity vector
	ImGui::Text("Steering angle: %d", (int)car->getSteeringAngle());	//Steering angle (delta)
	//Side slip angle (beta)
	//Rotation angle (yaw rate)
	//Slip angle front wheel
	//Slip angle rear wheels
	//Local velocity vector
	
	ImGui::End();

	//std::cout << "Gear: " << m_current_gear << std::endl;
	//std::cout << "RPM: " << calcNewRPM() << std::endl;
	//std::cout << "Wheel force: " << ForceWheel().magnitude() << std::endl;
	//std::cout << "Brake force: " << ForceBraking().magnitude() << std::endl;
}
