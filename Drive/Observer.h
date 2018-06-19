#pragma once

class Car;

class Observer
{
public:
	virtual			~Observer() {};
	virtual void	onNotify(Car& car) = 0;

	virtual void	getEntity(const Car& car) = 0;
	virtual Car&	setEntity(Car& car) = 0;
};

