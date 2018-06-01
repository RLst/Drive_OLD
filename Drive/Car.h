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
	Matrix3		m_local;
	Matrix3		m_world;

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

	float		getWheelTorque();				//Gets the wheel torque of the car by other calcs
	float		getWheelRadius();				//Get wheel radius by calculating wheel sizes etc
	float		getEngineTorque();				//Retrieves engine torque from a torque curve?
	float		getGearRatio(GEAR gear);
	float		getFinalDriveRatio() { return m_gearRatio.final; }

	Vector2		getHeading();

	Vector2		getForceDrag();
	Vector2		getForceRollResist();
	Vector2		getForceTraction();
	Vector2		getForceGravity();
	Vector2		getForceLongitude();
	Vector2		getForceBraking();

	Vector2		getAccel(float deltaTime);
	Vector2		getVelNew(float deltaTime);
	Vector2		getPosNew(float deltaTime);

	float		getEngineVelocity();
	float		getWheelAngularVelocity();

};
