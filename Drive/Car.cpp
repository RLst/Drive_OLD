#include "Car.h"
#include "GameDefines.h"
#include <Input.h>
#include <Texture.h>
#include <Renderer2D.h>
#include <cassert>

Car::Car(const char * textureFilePath)
{
	//Pseudo steering
	m_rotateSpeed = 3.0f;
	m_rotateAllowance = NULL;
	m_rotateAllowanceVel = 5.0f;

	//Transformations
	m_pos = Vector3();
	m_vel = Vector3();
	m_accel = Vector3();
	m_zRotation = NULL;

	//Constants/coefficients
	m_coeffDrag = 0.3f;		//For a Corvette
	m_factorRR = 30.0f;		//For the average car driving on tarmac

	//Physics
	m_mass = 1250.00f;
	m_areaFront = 2.2f;

	//Engine
	m_rpm = 1000.0;
	m_throttle = NULL;

	//Braking
	m_cBraking = 10000.0f;
	m_brake = NULL;

	//Transmission
	m_gearRatio.reverse = -2.90f;
	m_gearRatio.neutral = 0.0f;
	m_gearRatio.first = 2.66f;
	m_gearRatio.second = 1.78f;
	m_gearRatio.third = 1.30f;
	m_gearRatio.fourth = 1.0f;
	m_gearRatio.fifth = 0.74f;
	m_gearRatio.sixth = 0.5f;
	m_gearRatio.final = 3.42f;
	m_current_gear = FIRST;
	m_transmissionEff = 0.8f;

	//Dimensions
	m_wheelRadius = 0.34f;
	m_mu = 1.0f;

	//Weight
	m_wheelBase = 1.5f;

	//Texture
	m_texture = new aie::Texture(textureFilePath);
}

Car::~Car()
{}

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
	//30 for smooth normal roads; 20000-25000 for caterpillar tracks
	return cDrag() * m_factorRR;
}

Vector3 Car::ForceWheel()
{
	return Heading() * EngineTorque(m_rpm) * GearRatio(CurrentGear()) * GearRatio(FINAL) * m_transmissionEff / WheelRadius();
}

Vector3 Car::ForceBraking()
{
	//Brakes only work if the car is moving...
	if (m_vel.magnitude() > 0) {
		return -Heading() * m_cBraking * m_brake;
	}
	return Vector3();  //...otherwise return a null vector
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
	return ForceWheel() + ForceBraking() + ForceDrag() + ForceRollResist();
	//return ForceTraction() + ForceBraking() + ForceDrag() + ForceRollResist();
}

float Car::EngineTorque(float rpm)
{
	//TEMP!!
	return 500.0f * m_throttle;			//Return some arbitrary torque (Nm) * throttle multiplier

	//Need: RPM, Throttle amount 0-1.0f
	//float rpm = calcRPM();
	//float throttle = Throttle();
	//To be completed...
}

float Car::WheelTorque()
{
	return EngineTorque(m_rpm) * GearRatio(CurrentGear()) * GearRatio(FINAL) * m_transmissionEff;
}

float Car::WheelAngularVel()
{
	float result;
	result = m_vel.magnitude() / WheelRadius();		//.magnitude() because need to return a float
	return result;
}
//float Car::WheelAngularVel()  //ANOTHER ONE
//{
//	//TEMP; 
//	return m_rpm / GearRatio(CurrentGear()) * GearRatio(FINAL) * 2 * PI / 60.0f;
//}

float Car::Weight()
{
	return m_mass * GRAVITY;
}


float Car::WeightOnFrontAxle()
{
	return ((m_distRAxle / m_wheelBase) * Weight()) - ((m_heightCM / m_wheelBase) * m_mass * m_accel.magnitude());		//Not sure about the last part
}

float Car::WeightOnRearAxle()
{
	return ((m_distFAxle / m_wheelBase) * Weight()) + ((m_heightCM / m_wheelBase) * m_mass * m_accel.magnitude());
}

void Car::onThrottle()
{
	static float onThrottleAmount = 0.05f;
	m_throttle += onThrottleAmount;
	//Clamp
	if (m_throttle > 1.0f)
		m_throttle = 1.0f;
}

void Car::offThrottle()
{
	static float offThrottleAmmount = 0.25f;
	m_throttle -= offThrottleAmmount;
	//Clamp
	if (m_throttle < 0)
		m_throttle = 0;
}

void Car::onBrake()
{
	static float brakeAmount = 0.05;
	m_brake += brakeAmount;
	//Clamp
	if (m_brake > 1.0f)
		m_brake = 1.0f;
}

void Car::offBrake()
{
	static float offBrakeAmount = 0.25f;
	m_brake -= offBrakeAmount;
	//Clamp
	if (m_brake < 0)
		m_brake = 0;
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
	default:
		assert(false);
	}
}

void Car::ShiftUp()
{
	m_current_gear++;
}

void Car::ShiftDown()
{
	m_current_gear--;
}

float Car::calcNewRPM()
{
	return WheelAngularVel() * GearRatio(CurrentGear()) * GearRatio(FINAL) * 60/2*PI;
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


void Car::onUpdate(float deltaTime)
{
	//Get input instance
	auto input = aie::Input::getInstance();

	////CONTROLS
	//Accelerate
	if (input->isKeyDown(aie::INPUT_KEY_I) ||
		input->isKeyDown(aie::INPUT_KEY_UP)) {
		onThrottle();
	}
	else
		offThrottle();
	
	//Brake
	if (input->isKeyDown(aie::INPUT_KEY_K) ||
		input->isKeyDown(aie::INPUT_KEY_DOWN)) {
		onBrake();
	}
	else
		offBrake();

	//Steer left
	if (input->isKeyDown(aie::INPUT_KEY_J)||
		input->isKeyDown(aie::INPUT_KEY_LEFT)) {

		//Simple steering limit in relation to car speed
		m_rotateAllowance = m_vel.magnitude()/m_rotateAllowanceVel;
		if (m_rotateAllowance > 1)	m_rotateAllowance = 1.0f;
		
		m_zRotation = m_rotateSpeed * m_rotateAllowance * deltaTime;
	}
	//Steer right
	else if (input->isKeyDown(aie::INPUT_KEY_L) ||
			input->isKeyDown(aie::INPUT_KEY_RIGHT)) {	
		
		//Simple steering limit in relation to car speed
		m_rotateAllowance = m_vel.magnitude() / m_rotateAllowanceVel;
		if (m_rotateAllowance > 1)	m_rotateAllowance = 1.0f;

		m_zRotation = -m_rotateSpeed * m_rotateAllowance * deltaTime;
	}
	else {
		m_zRotation = 0;
	}

	//Gear shifting
	if (input->wasKeyPressed(aie::INPUT_KEY_A)) {
		ShiftUp();
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_Z)) {
		ShiftDown();
	}

	////Find acceleration
	m_accel = calcAccel();

	////Find velocity
	m_vel = calcVel(deltaTime);

	//TEMP; Stop car from sliding 
	m_vel = Heading() * m_vel.magnitude();

	//Apply final transformations
	translate(m_vel);
	rotate(m_zRotation);

	//Calc and assign new rpm
	m_rpm = calcNewRPM();

	//DEBUG
	printDebugs();
}

void Car::onDraw(aie::Renderer2D * renderer)
{
	//Draw the car
	renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_worldTrans);
}

void Car::printDebugs()
{
	std::cout << "Gear: " << m_current_gear << std::endl;
	std::cout << "RPM: " << calcNewRPM() << std::endl;
	std::cout << "Wheel force: " << ForceWheel().magnitude() << std::endl;
	std::cout << "Brake force: " << ForceBraking().magnitude() << std::endl;
}

