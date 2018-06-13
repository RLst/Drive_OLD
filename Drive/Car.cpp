#include "Car.h"
#include "GameDefines.h"
#include <Input.h>
#include <Texture.h>
#include <Renderer2D.h>

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
	m_rpm = 1000.0;

	//Set Transmission
	m_gearRatio.reverse = -2.90f;
	m_gearRatio.neutral = 0;
	m_gearRatio.first = 2.66f;
	m_gearRatio.second = 1.78f;
	m_gearRatio.third = 1.30f;
	m_gearRatio.fourth = 1.0f;
	m_gearRatio.fifth = 0.74f;
	m_gearRatio.sixth = 0.5f;
	m_gearRatio.final = 3.42f;

	//Other sets
	m_steerSpeed = 2.0f;

	//Texture
	m_texture = new aie::Texture("../bin/textures/car.png");
}

Car::~Car()
{}

//Vector3 Car::ForceTraction()
//{
//	//Returns the force vector 
//	//Traction force = Wheel torque / Wheel radius
//	return Heading() * EngineForce();
//	//return Heading() * WheelTorque() * WheelRadius();
//}

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
	return ForceWheel() + ForceBraking() + ForceDrag() + ForceRollResist();
	//return ForceTraction() + ForceBraking() + ForceDrag() + ForceRollResist();
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

float Car::WheelAngularVel()
{
	//TEMP; SIMPLE
	return simpleWheelAngularVel();
}

float Car::simpleWheelAngularVel()
{
	float result;
	result = m_vel.magnitude() / WheelRadius();		//.magnitude() because need to return a float
	return result;
}

float Car::WeightOnFrontAxle()
{
	return ((m_distRAxle / m_wheelBase) * Weight()) - ((m_heightCM / m_wheelBase) * m_mass * m_accel.magnitude());		//Not sure about the last part
}

float Car::WeightOnRearAxle()
{
	return ((m_distFAxle / m_wheelBase) * Weight()) + ((m_heightCM / m_wheelBase) * m_mass * m_accel.magnitude());
}

float Car::oldRPM()
{
	return m_rpm;
}

float Car::simpleCalcRPM()
{
	return simpleWheelAngularVel() * GearRatio(CurrentGear()) * GearRatio(FINAL) * 60/2*PI;
}

//float Car::calcRPM()
//{ 
//	m_rpm = WheelAngularVel() * GearRatio(CurrentGear()) * GearRatio(FINAL) * 60/2*PI;
//	return m_rpm;	//???? Required
//}

float Car::Throttle()
{
	return 0.5f;
}

float Car::EngineTorque(float rpm)
{
	//Need: RPM, Throttle amount 0-1.0f
	//float rpm = calcRPM();
	//float throttle = Throttle();
	//To be completed...

	//TEMP!!
	return simpleEngineTorque();			///TEMP.. in Newton Metres; To be completed
}

float Car::simpleEngineTorque()
{
	return 100.0f;			//Return some arbitrary torque (Nm) * throttle multiplier
}

Vector3 Car::ForceWheel()
{
	//TEMP: oldRPM() just for temps... refine later
	return Heading() * EngineTorque(oldRPM()) * GearRatio(CurrentGear()) * GearRatio(FINAL) * m_transEfficiency / WheelRadius();
}

GEAR Car::CurrentGear()
{
	return m_current_gear;
}

float Car::GearRatio(GEAR gear)
{
	switch (gear) {
	case REVERSE:
		return m_gearRatio.reverse;
		break;
	case NEUTRAL:
		return m_gearRatio.neutral;
		break;
	case FIRST:
		return m_gearRatio.first;
		break;
	case SECOND:
		return m_gearRatio.second;
		break;
	case THIRD:
		return m_gearRatio.third;
		break;
	case FOURTH:
		return m_gearRatio.fourth;
		break;
	case FIFTH:
		return m_gearRatio.fifth;
		break;
	case SIXTH:
		return m_gearRatio.sixth;
		break;
	case FINAL:
		return m_gearRatio.final;
		break;

	}
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
	return m_worldTrans.yAxis.normalised();		//Should already be normalised anyways
}

float Car::cDrag()
{
	return 0.5f * m_coeffDrag * m_areaFront * RHO * m_vel.dot(m_vel);
}

float Car::cRR()
{
	//m_factorRR is a drag constant multiple
	//Adjust accordingly
	//General values:
	//30 for smooth normal roads
	//20000-25000 for caterpillar tracks
	return cDrag() * m_factorRR;
}

void Car::onUpdate(float deltaTime)
{
	//Get input instance
	auto input = aie::Input::getInstance();

	////CONTROLS
	if (input->isKeyDown(aie::INPUT_KEY_I)) {	//Accelerate
	}
	if (input->isKeyDown(aie::INPUT_KEY_K)) {	//Brake
	}

	if (input->isKeyDown(aie::INPUT_KEY_J)) {	//Steer left
		//Simple
		m_zRotation = m_steerSpeed * deltaTime;
	}
	else if (input->isKeyDown(aie::INPUT_KEY_L)) {	//Steer right
		//Simple
		m_zRotation = -m_steerSpeed * deltaTime;
	}
	else {
		m_zRotation = 0;
	}

	////Calculate resistant forces
	ForceDrag();	//Done
	ForceRollResist();	//Done

	////Find total longitudinal force
	ForceLongitudinal();

	////Find acceleration
	m_accel = calcAccel();

	////Find velocity
	m_vel = calcVel(deltaTime);

	//TEMP; Stop car from sliding 
	m_vel = Heading() * m_vel.magnitude();

	//Apply final tranformations
	translate(m_vel);
	rotate(m_zRotation);
}

void Car::onDraw(aie::Renderer2D * renderer)
{
	//Draw the car
	renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_worldTrans);
}
