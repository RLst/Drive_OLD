#pragma once
#include <cmath>
#include <Vector2.h>
#include <Matrix3.h>

class Vector2;

class Car
{
private:
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
	Vector2		m_vel;
	float		m_rot;

	float		m_slopeAngle;

	//Transformations
	Matrix3		m_localTrans;
	Matrix3		m_worldTrans;

	//Constants
	float		m_cDrag;
	float		m_cRR;
	float		g_gravity = 9.81f;
	float		m_cBrake;

	//Specifications
	float		m_mass;

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

	Vector2		Heading();					//u; Vector

	Vector2		ForceDrag();
	Vector2		ForceRollResist();
	Vector2		ForceTraction();				//Ftraction; Vector
	Vector2		ForceGravity();
	Vector2		ForceLongitude();
	Vector2		ForceBraking();

	Vector2		getAccel(float deltaTime);
	Vector2		getVelNew(float deltaTime);
	Vector2		getPosNew(float deltaTime);

	float		EngineVelocity();
	float		WheelAngularVelocity();

};
