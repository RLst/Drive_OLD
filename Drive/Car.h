#pragma once
#include <cmath>
#include <Vector2.h>
#include <Matrix3.h>

const float PI = 3.1415926535897932384626433832795f;

class Vector2;

class Car
{
private:
	//Physics
	float		m_cDrag = 0.4257;		//Corvette
	float		m_cRR = 12.8;			//Corvette; unconfirmed
	float		g_gravity = 9.81f;
	float		m_cBrake;

	enum GEAR
	{
		REVERSE = -1,
		NEUTRAL = 0,
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH,
		SIXTH,
	};

	//Core
	Vector2		m_pos;
	Vector2		m_vel;							//v; vector
	float		m_rot;

	float		m_slopeAngle;

	//Transformations
	Matrix3		m_localTrans;
	Matrix3		m_worldTrans;

	//Constants


	//Specifications
	float		m_mass;
	float		m_wheelRadius;

	//Engine

	//Gears
	GEAR m_current_gear;
	struct {
		float reverse;
		float neutral;
		float first;
		float second;
		float third;
		float fourth;
		float fifth;
		float sixth;
		float final;
	} m_gearRatio;

public:
	Car();
	~Car();

	float		WheelTorque();				//Gets the wheel torque of the car by other calcs
	float		WheelRadius();				//Get wheel radius by calculating wheel sizes etc
	float		EngineTorque();				//Retrieves engine torque from a torque curve?
	float		GearRatio(GEAR gear);
	float		FinalDriveRatio() { return m_gearRatio.final; }
	float		EngineForce();

	//Heading
	Vector2		Heading();						//Normalised vector of the direction the car is facing

	//Forces
	Vector2		ForceTraction();				//Ftraction; vector
	Vector2		ForceDrag();					//Fdrag; vector
	Vector2		ForceRollResist();				//Frollresist; vector
	Vector2		ForceLongitude();				//Flong; vector
	Vector2		ForceGravity();
	Vector2		ForceBraking();

	//Integration
	Vector2		Accel();
	Vector2		Velocity(float deltaTime);
	Vector2		Position(float deltaTime);

	//Car specs
	float		EngineVelocity();
	float		WheelAngularVelocity();

};
