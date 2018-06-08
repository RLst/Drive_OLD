#include "Car.h"

Vector3 Car::ForceTraction()
{
	//Returns the force vector 
	//Traction force = Wheel torque / Wheel radius
	return Heading() * EngineForce();
	//return Heading() * WheelTorque() * WheelRadius();
}

Vector3 Car::ForceDrag()
{
	//Drag force = - Drag constant * velocity * |velocity|
	return -m_coeffDrag * m_vel * m_vel.magnitude();
}

Vector3 Car::ForceRollResist()
{
	//Rolling Resistance Force = RollResist constant * Velocity
	return -cRR() * m_vel;
}

Vector3 Car::ForceLongitudinal()
{
	//Longitudinal force = Traction force + Drag force + RollResist force + Gravity force
	return ForceTraction() + ForceBraking() + ForceDrag() + ForceRollResist();
}

//Vector3 Car::ForceGravity()
Vector3 Car::ForceBraking()
{
	Vector3 brakeForce;
	//Brakes only work if the car is moving...
	if (m_vel.magnitude() > 0) {
		return -Heading() * getBrakeFactor();
	}
	else {	//...otherwise return a null vector
		return Vector3();
	}
}

float Car::getBrakeFactor()
{
	return m_cBraking;
}

Vector3 Car::ForceWheelTractionMax(WHEEL wheel, float Weight)
{
	//Inverse of Heading * Braking constant
	return Heading() * m_cBrake;
}

Vector3 Car::calcAccel()
{
	return ForceLongitude() / m_mass;
}

Vector3 Car::calcVel(float deltaTime)
{
	return m_vel + deltaTime * Accel();
}

Vector3 Car::calcPos(float deltaTime)
{
	return m_pos + deltaTime * Velocity(deltaTime);
}

//float Car::WheelAngularVelocity()
//{
//	return 2 * PI * en;
//}

float Car::WheelTorque()
float Car::EngineForce()
{
	return m_arbEngineForce;
}
{
	return EngineTorque() * GearRatio(m_current_gear) * FinalDriveRatio();
}

Vector2 Car::Heading()
{
	return m_worldTrans.yAxis;		//Should already be normalised
}

Car::~Car()
{}
