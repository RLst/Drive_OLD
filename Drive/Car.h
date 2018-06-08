#pragma once
#include <cmath>
#include <Vector3.h>
#include <Matrix3.h>

const float PI = 3.1415926535897932384626433832795f;


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
	//Physics
	//float		m_coeffDrag = 0.4257;		//Corvette
	//float		m_cRR = 12.8;			//Corvette; unconfirmed

	//Core
	Vector3		m_pos;
	Vector3		m_vel;							//v; vector
	float		m_zRotation;

	float		m_slopeAngle;

	//Transformations
	Matrix3		m_localTrans;
	Matrix3		m_worldTrans;

	//Constants
	float		m_coeffDrag;
	float		m_factorRR;						//Factor to multiply with Drag constant to get Roll Resist constant

	//Specifications
	float		m_mass;
	float		m_wheelRadius;

	//Engine
	float		m_arbEngineForce;

	//Gears
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
	GEAR m_current_gear;
	struct {
		float	reverse;
		float	neutral;
		float	first;
		float	second;
		float	third;
		float	fourth;
		float	fifth;
		float	sixth;
		float	final;
	} m_gearRatio;

	enum WHEEL
	{
		FL = 0,
		FR = 1,
		RL = 2,
		RR = 3
	};

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
	Vector3		Heading();						//Normalised vector of the direction the car is facing

	//Constants; Maybe these are too basic to be in its own function
	float		cDrag();						
	float		cRR();

	//Forces
	Vector3		ForceTraction();				//Ftraction; vector
	Vector3		ForceDrag();					//Fdrag; vector
	Vector3		ForceRollResist();				//Frollresist; vector
	Vector3		ForceLongitudinal();				//Flong; vector
	//Vector3		ForceGravity();

	//Braking
	Vector3		ForceBraking();
	float		getBrakeFactor();				//Returns the current brake factor (brake amount, calculated from brake input between 0-1.0f?) 

	//Car specs
	float		EngineVelocity();
	float		WheelAngularVelocity();
	//Integration
	Vector3		calcAccel();
	Vector3		calcVel(float deltaTime);
	Vector3		calcPos(float deltaTime);

};
