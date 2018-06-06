#include "Car.h"

Vector2 Car::ForceDrag()
{
	//Drag force = - Drag constant * velocity * |velocity|
	return (-m_cDrag * m_vel * m_vel.absolute());
}

Vector2 Car::ForceRollResist()
{
	//Rolling Resistance Force = RollResist constant * Velocity
	return (-m_cRR * m_vel);
}

Vector2 Car::ForceTraction()
{
	//Returns the force vector 
	//Traction force = Wheel torque / Wheel radius
	return Heading() * WheelTorque() * WheelRadius();
}

Vector2 Car::ForceGravity()
{
	return (Heading() * m_mass) * g_gravity * sinf(m_slopeAngle);
}

Vector2 Car::ForceLongitude()
{
	//Longitudinal force = Traction force + Drag force + RollResist force + Gravity force
	return ForceDrag() + ForceRollResist() + ForceGravity()+ ForceTraction();
}

Vector2 Car::ForceBraking()
{
	//Inverse of Heading * Braking constant
	return Heading() * m_cBrake;
}

float Car::WheelAngularVelocity()
{
	return 2 * PI * en;
}

float Car::WheelTorque()
{
	return EngineTorque() * GearRatio(m_current_gear) * FinalDriveRatio();
}

Vector2 Car::Heading()
{
	return m_worldTrans.yAxis;		//Should already be normalised
}

Car::~Car()
{}
