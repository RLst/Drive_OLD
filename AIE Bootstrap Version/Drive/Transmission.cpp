#include "Transmission.h"



Transmission::Transmission()
{
	//Initialise gear ratios
	m_ratio.reverse = -2.90f;
	m_ratio.neutral = 0;
	m_ratio.first = 2.66f;
	m_ratio.second = 1.78f;
	m_ratio.third = 1.30f;
	m_ratio.fourth = 1.0f;
	m_ratio.fifth = 0.74f;
	m_ratio.sixth = 0.5f;
	m_ratio.Final = 3.42f;
	m_currentGear = FIRST;
	m_efficiency = 0.8f;
}


Transmission::~Transmission()
{
}

Transmission::Transmission(
	float final, float reverse, float first, 
	float second, float third, float fourth, 
	float fifth, float sixth)
{
	m_ratio.Final = final;
	m_ratio.reverse = reverse;
	m_ratio.first = first;
	m_ratio.second = second;
	m_ratio.third = third;
	m_ratio.fourth = fourth;
	m_ratio.fifth = fifth;
	m_ratio.sixth = sixth;
	m_ratio.neutral = 0;
}

void Transmission::shiftUp()
{
	//Convert to an int
	int currentGear = m_currentGear;

	//Shift gear up
	m_currentGear = (GEAR)currentGear + 1;

	//Convert back
}

void Transmission::shiftDown()
{
	//Convert to an int
	int currentGear = m_currentGear;

	//Shift gear up
	m_currentGear = (GEAR)currentGear - 1;

	//Convert back
}

void Transmission::setGear(GEAR gear)
{
	//Convert 
}

