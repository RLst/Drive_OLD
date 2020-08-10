#pragma once


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

class Transmission
{
	float m_efficiency;
	int m_currentGear;

	struct {
		float	reverse;
		float	neutral;
		float	first;
		float	second;
		float	third;
		float	fourth;
		float	fifth;
		float	sixth;
		float	Final;
	} m_ratio;

public:
	Transmission();
	~Transmission();

	Transmission(
		float	final,
		float	reverse,
		float	first,
		float	second,
		float	third,
		float	fourth = -1,
		float	fifth = -1,
		float	sixth = -1);

	//void		startup(
	//	float	final,
	//	float	reverse,
	//	float	first,
	//	float	second,
	//	float	third,
	//	float	fourth = -1,
	//	float	fifth = -1,
	//	float	sixth = -1,
	//	float	neutral = 0);
	
	void		shiftUp();
	void		shiftDown();
	void		setGear(GEAR gear);
	GEAR		getGear();
	
};

