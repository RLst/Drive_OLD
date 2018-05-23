#include "Car.h"

namespace pkr {

float Car::getForceDrag()
{
	return (-m_cDrag * m_vel * abs(m_vel));
}

float Car::getForceRollResist()
{
	return (-m_cRR * m_vel);
}

float Car::getForceTraction()
{
	return getTorqueWheel * getWheelRadius;
}

float Car::getGravity()
{
	return m_gravity;
}

float Car::getForceLongitude()
{
	return getForceTraction() + getForceDrag() + getForceRollResist() + getGravity();
}

Car::~Car()
{}


}