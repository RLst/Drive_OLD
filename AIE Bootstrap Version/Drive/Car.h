#pragma once

#include <Vector3.h>
#include <Matrix3.h>

#include "SceneObject.h"
#include "GUI.h"

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
inline const GEAR& operator ++ (GEAR& gear, int) {
	if (gear == SIXTH) return SIXTH;
	int temp = gear;
	return gear = static_cast<GEAR>(++temp);
}
inline const GEAR& operator -- (GEAR& gear, int) {
	if (gear == REVERSE) return REVERSE;
	int temp = gear;
	return gear = static_cast<GEAR>(--temp);
}

enum WHEEL
{
	FL = 0,
	FR = 1,
	RL = 2,
	RR = 3
};


class Car : public SceneObject
{
private:
	//ALL UNITS IN SI unless otherwise specified

	//FOR TESTING
	//float m_arbFactorSteering;
	//float m_rotateAllowance;
	//float m_rotateAllowanceVel;

	////Transforms
	//Linear
	Vector3		m_accel = Vector3();	//Zero all these values as to avoid weird offscreen bugs
	Vector3		m_vel = Vector3();
	Vector3		m_pos = Vector3();
	Vector3		m_forceTotal = Vector3();
	Vector3		m_forceResistance = Vector3();
	Vector3		m_forceTraction = Vector3();
	float		m_torqueTotal = 0;
	//Vector3		m_velLateral;
	//Vector3		m_velLongitudinal;

	//Angular (these are floats because only one axis of rotation in 2D (Z)
	float		m_angAccel = 0;			
	float		m_angVel = 0;			//omega
	float		m_angPos = 0;
	//Vector3		m_forceLatFront = Vector3();
	//Vector3		m_forceLatRear = Vector3();

	//Dimensions
	float		m_width;
	float		m_length;

	////Physics
	float		m_mass;
	float		m_inertia;					//Say 1000?
	float		m_areaFront;
	float		m_coeffDrag;
	float		m_factorRR;					//Factor to multiply with Drag constant to get Roll Resist constant ie: 30 for rolling, 20000 for caterpillar tracks
	float		m_corneringStiffness;		//Say 2000-3000 or so?

	//Engine		
	float		m_throttleLoad = 0;			//Throttle amount/load "normalised"
	float		m_rpm;
	float		m_redline;					
		
	//Braking		
	float		m_brakeLoad = 0;			//Braking amount/load "normalised"
	float		m_brakeConst;				//Braking constant (kinda general)

	//Steering
	float		m_steerDelta = 0;			//Steering amount in degrees
	float		m_steerLimit;				//Steer limit in angles
	float		m_steerGain;				//In degrees; How much to steer per function call
	float		m_steerReduce;				//In degrees; How steering to reduce/reset when steering wheel let of

	//Tyres and wheels
	float		m_wheelRadius;				//metres
	float		m_mu;						//Tire friction coefficient
	float		m_tyreWidth;				//Millimetres
	float		m_tyreAspectRatio;			//Percentage
	float		m_tyreDiameter;				//Inches

	float		m_wheelBase;				//Distance between axles ( front + rear axles)
	float		m_weightDistribFront;		//Front weight distribution; distance between front axle to COM
	float		m_distCMFront;				//Distance from CG to front axle
	float		m_distCMRear;				//Distance from CG to rear axle
	float		m_heightCM;					//Height of centre of mass

	float		m_wheelTrack;				//Distance between the centreline of wheels of the same axle
	float		m_angVelWheel = 0;				//Wheel rotation rate

	////////////////
	//TEMP: Gears
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
	/////////////////////

	//Sprites
	aie::Texture*	m_texture;

public:
	Car();
	Car(const char * textureFilePath);
	~Car();

	//GUI - getters are bad practice
	float		getRPM() const { return m_rpm; }
	const char* getGEARstr() const;				//Get gear as a string for GUI
	float		getForceWheel() const;
	float		getVelocity() const;
	float		getSteeringAngle() const { return m_steerDelta; }

	Vector3		getAccel() const { return m_accel; }
	Vector3		getVel() const { return m_vel; }
	Vector3		getPos() const { return m_pos; }
	float		getAngAccel() const { return m_angAccel; }
	float		getAngVel() const { return m_angVel; }
	float		getAngPos() const { return m_angPos; }

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

	//Resistances
	Vector3		ForceDrag();					//Return force of air resistance
	Vector3		ForceRollResist();				//Returns force of rolling resistance

	//Longitudinal
	Vector3		ForceLongitudinal();			//Returns sum longitudinal force on car

	//Engine	
	float		EngineTorque(float rpm);		//Lookup actual engine torque from curve or table

	//Wheel
	float		WheelTorque();					//Gets the wheel torque of the car by other calcs
	float		WheelRadius() { return m_wheelRadius; }	//Get wheel radius by calculating wheel sizes etc
	float		WheelAngularVel();

	//Weight transfer
	float		Weight();						//Total weight of the car
	float		WeightOnFrontAxle();
	float		WeightOnRearAxle();
	float		Inertia();

	//Transmission
	GEAR		CurrentGear();					//Returns currently selected gear
	float		GearRatio(GEAR gear);			//Returns the actual gear ratio of input gear
	void		ShiftUp();
	void		ShiftDown();

	//Accelerating
	void		onThrottle();									//Increase throttle a bit
	void		offThrottle();									//Take 'foot' off the throttle
	//float		Throttle() const { return m_throttle; }			//Returns current throttle position (0.0 - 1.0)
	//void		setThrottle(float val) { m_throttle = val; }

	//Braking
	void		onBrake();							
	void		offBrake();
	//float		Brake() const { return m_brake; }

	//Steering
	void		leftTurn();						//Turn steering wheel left
	void		rightTurn();					//Turn steering wheel right
	void		offTurn();						//Steering wheel released, resets to 0

	//Integration
	float		calcNewRPM();					//RPM calculated back from the wheel (Do after calculating ForceWheel)
	Vector3		calcAccel();
	Vector3		calcVel(float deltaTime);
	Vector3		calcPos(float deltaTime);

	//UPDATE
	void		onUpdate(float deltaTime);
	void		onDraw(aie::Renderer2D* renderer);
};