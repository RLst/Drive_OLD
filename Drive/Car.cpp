#include "Car.h"
#include "GameDefines.h"

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
//{
//	return (Heading() * m_mass) * g_gravity * sinf(m_slopeAngle);
//}

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

float Car::Weight()
{
	return m_mass * GRAVITY;
}

Vector3 Car::testForceWheelTractionMax(WHEEL wheel, float Weight)
{

	return Vector3();
}

float Car::WheelRadius()
{
	return m_wheelRadius;
}

float Car::WeightOnFrontAxle()
{
	return ((m_distRAxle / m_wheelBase) * Weight()) - ((m_heightCM / m_wheelBase) * m_mass * m_accel.magnitude());		//Not sure about the last part
}

float Car::WeightOnRearAxle()
{
	return ((m_distFAxle / m_wheelBase) * Weight()) + ((m_heightCM / m_wheelBase) * m_mass * m_accel.magnitude());
}

float Car::RPM()
{ 
	return 4500;
}

float Car::Throttle()
{
	return 0.5f;
}

float Car::getEngineTorqueCurve()
{
	//Need: RPM, Throttle amount 0-1.0f
	float rpm = RPM();
	float throttle = Throttle();
	return 200;			///TEMP.. in Newton Metres; To be completed
}

Vector3 Car::testForceDrive()
{
	return Heading() * getEngineTorqueCurve() * GearRatio(getCurrentGear()) * GearRatio(FINAL) * m_transEfficiency / WheelRadius();
}

Vector3 Car::calcAccel()
{
	return ForceLongitudinal() / m_mass;
}

Vector3 Car::calcVel(float deltaTime)
{
	return m_vel + calcAccel() * deltaTime;
}

Vector3 Car::calcPos(float deltaTime)
{
	return m_pos + calcVel(deltaTime) * deltaTime;
}

Vector3 Car::Heading()
{
	return m_worldTrans.yAxis.normalised();		//Should already be normalised
}

float Car::cDrag()
{
	return 0.5 * m_coeffDrag * m_areaFront * RHO * m_vel.dot(m_vel);
}

float Car::cRR()
{
	return cDrag() * m_factorRR;
}

Car::Car()
{
	m_pos = Vector3();
	m_vel = Vector3();
	m_accel = Vector3();

	//Constants/coefficients
	m_coeffDrag = 0.3f;		//For a Corvette
	m_factorRR = 30.0f;		//For the average car driving on tarmac
	m_cBraking = 100.0f;

	//Set Engine

	//Set Transmission

}

Car::~Car()
{}
