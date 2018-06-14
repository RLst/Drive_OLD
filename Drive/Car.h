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

	//FOR TESTING
	float m_steerSpeed;
	////TYRE_SPEED			m_tyreSpeedRating;
	////TYRE				m_tyreConstruction;

	//Transforms
	Vector3		m_accel;
	Vector3		m_vel;
	Vector3		m_pos;
	float		m_zRotation;

	//Resistance
	float		m_coeffDrag;
	float		m_factorRR;						//Factor to multiply with Drag constant to get Roll Resist constant
												//ie: 30 for rolling, 20000 for caterpillar tracks

	//Physical
	float		m_mass;
	float		m_areaFront;

	//Engine
	//float		m_arbEngineForce;
	float		m_rpm;
	float		m_throttle;

	//Braking
	float		m_cBraking;
	float		m_brake;

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
	float m_transmissionEff;

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
	Car(const char * textureFilePath);
	~Car();

	//Heading
	Vector3		Heading();						//Normalised vector of the direction the car is facing

	//Constants; Maybe these are too basic to be in its own function
	float		cDrag();						
	float		cRR();

	///////////
	////Forces
	/////////
	Vector3		ForceWheel();					//aka. ForceWheel; Driving force exerted by drive wheels; ultimately the EngineForce()?

	//Braking
	Vector3		ForceBraking();					//Returns car's braking force
	float		getBrakeFactor();				//Returns the current brake factor (brake amount, calculated from brake input between 0-1.0f?) 

	//Resistances
	Vector3		ForceDrag();					//Return force of air resistance
	Vector3		ForceRollResist();				//Returns force of rolling resistance

	//Longitudinal
	Vector3		ForceLongitudinal();			//Returns sum longitudinal force on car

	//Engine	
	float		EngineTorque(float rpm);		//Lookup actual engine torque from curve or table

	//Wheel
	float		WheelTorque();					//Gets the wheel torque of the car by other calcs
	float		WheelRadius();					//Get wheel radius by calculating wheel sizes etc
	float		WheelAngularVel();

	//Weight transfer
	float		Weight();						//Total weight of the car
	float		WeightOnFrontAxle();
	float		WeightOnRearAxle();

	//Transmission
	GEAR		CurrentGear();					//Returns currently selected gear
	float		GearRatio(GEAR gear);			//Returns the actual gear ratio of input gear

	//Accelerator pedal
	void		onThrottle();					//Increase throttle a bit
	void		offThrottle();					//Take 'foot' off the throttle
	void		setThrottle(float val) { m_throttle = val; }
	float		Throttle() const;				//Returns current throttle position (0.0 - 1.0)

	//Integration
	float		calcNewRPM();					//RPM calculated back from the wheel (Do after calculating ForceWheel)
	Vector3		calcAccel();
	Vector3		calcVel(float deltaTime);
	Vector3		calcPos(float deltaTime);

	//////////
	//SIMPLES
	////////
	float		WheelAngularVel();

	//UPDATE
	void		onUpdate(float deltaTime);
	void		onDraw(aie::Renderer2D* renderer);
};
