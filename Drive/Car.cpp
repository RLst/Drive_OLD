#include "Car.h"

Vector2 Car::getForceDrag()
{
	//Drag force = - Drag constant * velocity * |velocity|
	return (-m_cDrag * m_vel * m_vel.absolute());
}

Vector2 Car::getForceRollResist()
{
	//Rolling Resistance Force = RollResist constant * Velocity
	return (-m_cRR * m_vel);
}

Vector2 Car::getForceTraction()
{
	//Returns the force vector 
	//Traction force = Wheel torque / Wheel radius
	return getHeading() * getWheelTorque() * getWheelRadius();
}

Vector2 Car::getForceGravity()
{
	return (getHeading() * m_mass) * g_gravity * sinf(m_slopeAngle);
}

Vector2 Car::getForceLongitude()
{
	//Longitudinal force = Traction force + Drag force + RollResist force + Gravity force
	return getForceDrag() + getForceRollResist() + getForceGravity()+ getForceTraction();
}

Vector2 Car::getForceBraking()
{
	//Inverse of Heading * Braking constant
	return getHeading() * m_cBrake;
}

float Car::getWheelAngularVelocity()
{
	return 2 * PI * en;
}

float Car::getWheelTorque()
{
	return getEngineTorque() * getGearRatio(m_current_gear) * getFinalDriveRatio();
}

Vector2 Car::getHeading()
{
	return m_vel.normalised();
}

Car::~Car()
{}
