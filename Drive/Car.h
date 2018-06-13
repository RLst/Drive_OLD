#pragma once
#include <cmath>
#include <Vector3.h>
#include <Matrix3.h>
#include "SceneObject.h"

namespace aie {
	class Texture;
}
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
	FINAL = 99
};
enum WHEEL
{
	FL = 0,
	FR = 1,
	RL = 2,
	RR = 3
};
//enum TYRE_SPEED {
//	J = 100,
//	K = 110,
//	L = 120,
//	M = 130,
//	N = 140,
//	P = 150,
//	Q = 160,
//	R = 170,
//	S = 180,
//	T = 190,
//	U = 200,
//	H = 210,
//	V = 240,
//	W = 270,
//	Y = 300,
//	VR,
//	ZR
//};


class Car : public SceneObject
{
private:
	//ALL UNITS IN SI unless otherwise specified

	//Physics
	//float		m_coeffDrag = 0.4257;			//Corvette
	//float		m_cRR = 12.8;					//Corvette; unconfirmed

	//Temp
	float m_steerSpeed;

	//Core
	Vector3		m_accel;
	Vector3		m_vel;							//v; vector
	Vector3		m_pos;
	float		m_zRotation;

	//Constants
	float		m_coeffDrag;
	float		m_factorRR;						//Factor to multiply with Drag constant to get Roll Resist constant

	////Specifications
	float		m_mass;
	float		m_areaFront;

	////TYRE_SPEED			m_tyreSpeedRating;
	////TYRE				m_tyreConstruction;

	//Engine
	float		m_arbEngineForce;
	float		m_rpm;

	//Braking
	float		m_cBraking;

	//Gears
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
	GEAR m_current_gear;
	float m_transEfficiency;

	//Tyres and wheels
	float		m_wheelRadius;
	float		m_mu;							//Tire friction coefficient
	float		m_tyreWidth;					//Millimetres
	float		m_tyreAspectRatio;				//Percentage
	float		m_tyreDiameter;					//Inches
	float		m_wheelBase;					//Distance between axles
	float		m_wheelTrack;					//Distance between the centreline of wheels of the same axle
	float		m_heightCM;						//Height of centre of mass
	float		m_distFAxle;					//Distance from CG to front axle
	float		m_distRAxle;					//Distance from CG to rear axle

	//Texture
	aie::Texture*	m_texture;


public:
	Car();
	~Car();

	//Heading
	Vector3		Heading();						//Normalised vector of the direction the car is facing

	//Constants; Maybe these are too basic to be in its own function
	float		cDrag();						
	float		cRR();

	////Forces
	Vector3		ForceLongitudinal();			//Returns sum longitudinal force on car

	//Drive
	Vector3		ForceTraction();				//Returns car's driving force

	//Resistance
	Vector3		ForceDrag();					//Return force of air resistance
	Vector3		ForceRollResist();				//Returns force of rolling resistance

	//Braking
	Vector3		ForceBraking();					//Returns car's braking force
	float		getBrakeFactor();				//Returns the current brake factor (brake amount, calculated from brake input between 0-1.0f?) 

	//Weight transfer
	float		Weight();						//Total weight of the car
	float		WeightOnFrontAxle();
	float		WeightOnRearAxle();
	Vector3		testForceWheelTractionMax(WHEEL wheel, float Weight);		//Maximum force the wheel can exert

	//Wheel
	float		WheelRadius();					//Get wheel radius by calculating wheel sizes etc
	float		simpleWheelTorque();			//Gets the wheel torque of the car by other calcs
	
	float		simpleWheelAngularVel();
	float		WheelAngularVel();

	//Engine
	float		oldRPM();						//TEMP; needs to be called before calcRPM()
	float		simpleCalcRPM();				//RPM calculated from car velocity regardless of tire spin/slip
	float		calcRPM();						//RPM calculated back from the wheel

	float		Throttle();						//Current actual throttle

	float		simpleEngineTorque();			//Temporary function that returns some kinda engine torque for testing purposes
	float		EngineTorque(float rpm);					//Lookup actual engine torque from curve or table
	Vector3		ForceWheel();					//aka. ForceWheel; Driving force exerted by drive wheels; ultimately the EngineForce()?

	//*Transmission
	GEAR		CurrentGear();					//Returns currently selected gear
	float		GearRatio(GEAR gear);			//Returns the actual gear ratio of input gear

	//*Integration
	Vector3		calcAccel();
	Vector3		calcVel(float deltaTime);
	Vector3		calcPos(float deltaTime);


	//UPDATE
	void		onUpdate(float deltaTime);
	void		onDraw(aie::Renderer2D* renderer);
};
