#include "Car.h"

namespace pkr {

float Car::getForceDrag()
{
	return (-m_cDrag * m_vel * abs(m_vel));
}

Car::Car()
{
}


Car::~Car()
{
}
}