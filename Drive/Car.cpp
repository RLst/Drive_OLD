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


Car::~Car()
{
}
}