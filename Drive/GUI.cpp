#include "GUI.h"
#include <imgui.h>
#include "Car.h"

void GUI::draw(Car * car)
{
	ImGui::Begin("Car");
	ImGui::Text("Gear: %s", car->getGEARstr());
	ImGui::Text("RPM: %d", (int)car->getRPM());
	ImGui::NewLine();
	ImGui::Text("Accel: %f, %f", car->getAccel().x, car->getAccel().y);
	ImGui::Text("Vel: %f, %f", car->getVel().x, car->getVel().y);				//World velocity vector
	ImGui::Text("Pos: %f, %f", car->getPos().x, car->getPos().y);
	ImGui::NewLine();
	//ImGui::Text("Accel: %f, %f", car->getAccel().x, car->getAccel().y);
	//ImGui::Text("Vel: %f, %f", car->getVel().x, car->getVel().y);				//World velocity vector
	ImGui::Text("Pos: %f, %f", car->getWorldTrans().yAxis.x, car->getWorldTrans().yAxis.y);

	ImGui::NewLine();
	ImGui::Text("Steering angle: %d", (int)car->getSteeringAngle());	//Steering angle (delta)
	ImGui::Text("Ang Accel: %d", (int)car->getAngAccel());
	ImGui::Text("Ang Vel: %d", (int)car->getAngVel());
	ImGui::Text("Ang Pos: %d", (int)car->getAngPos());
																		
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
