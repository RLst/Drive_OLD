#pragma once
#include <cmath>
#include <Vector3.h>
#include <Matrix3.h>
#include "SceneObject.h"

class Car : public SceneObject
{
private:
	//ALL UNITS IN SI unless otherwise specified

	//Physics
	//float		m_coeffDrag = 0.4257;		//Corvette
	//float		m_cRR = 12.8;			//Corvette; unconfirmed

	//Core
	Vector3		m_accel;
	Vector3		m_vel;							//v; vector
	Vector3		m_pos;
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
	float		m_areaFront;
	float		m_mu;							//Tire friction coefficient

	//Engine
	float		m_arbEngineForce;

	//Braking
	float		m_cBraking;

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

	//Wheels
	float m_wheelBase;
	float m_wheelTrack;
	float m_heightCM;						//Height of centre of mass
	float m_distFAxle;						//Distance from CG to front axle
	float m_distRAxle;						//Distance from CG to rear axle
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

	//Car specs
	float		GearRatio(GEAR gear);
	float		FinalDriveRatio() { return m_gearRatio.final; }

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

	//Weight transfer
	float		Weight();
	Vector3		ForceWheelTractionMax(WHEEL wheel, float Weight);
	float		WeightOnFrontAxle();
	float		WeightOnRearAxle();

	//Wheel
	float		WheelTorque();				//Gets the wheel torque of the car by other calcs
	float		WheelRadius();				//Get wheel radius by calculating wheel sizes etc




	//Integration
	Vector3		calcAccel();
	Vector3		calcVel(float deltaTime);
	Vector3		calcPos(float deltaTime);

};
