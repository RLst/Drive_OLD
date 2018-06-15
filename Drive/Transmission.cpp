#include "Transmission.h"



Transmission::Transmission()
{
	//Initialise gear ratios
	ratio.reverse = -2.90f;
	ratio.neutral = 0;
	ratio.first = 2.66f;
	ratio.second = 1.78f;
	ratio.third = 1.30f;
	ratio.fourth = 1.0f;
	ratio.fifth = 0.74f;
	ratio.sixth = 0.5f;
	ratio.final = 3.42f;
	currentGear = FIRST;
	efficiency = 0.8f;
}


Transmission::~Transmission()
{
}
