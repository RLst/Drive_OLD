#pragma once
#include "GameDefines.h"

class Car;

class Observer
	//Subscriber
{
public:
	virtual		~Observer() {};

	virtual void	update(
		float rpm,
		float torque,		//Engine torque
		float velocity,
		GEAR gear,
		float throttle,
		float brake,
		float accel,
		float wheelForce) = 0;


	//What do I want to observe from my car?
	//> RPM
	//> Engine torque
	//> Current gear
	//> Velocity
	//> Throttle
	//> Brake
	//> (Clutch)
	//Other:
	//> Acceleration
	//> Wheel angular velocity
	//> Final gear ratio
	//> Current gear ratio

	//virtual void	onNotify(const Car& car) = 0;
	//virtual Car&	getMutable(Car* car) = 0;
	//virtual void	getImmutable(const Car& car) = 0;
};

