#pragma once
#include <cmath>

namespace pkr
{
	class Vector2;

	class Car
	{
	private:
		//Core
		Vector2		m_pos;
		Vector2		m_vel;
		Vector2		m_rot;

		//Constants
		float		m_cDrag;
		float		m_cRR;

		//TBS
		float		getTorqueWheel;
		float		getWheelRadius;


		float		getForceDrag();
