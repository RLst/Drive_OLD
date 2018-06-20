#pragma once
#include "Observer.h"
#include <vector>

class Car;

class Subject
	//Publisher
{
private:
	//std::vector<Observer*> m_observers;

protected:

	
public:
	//Subject();
	//~Subject();

	virtual void		notifyObserver() = 0;
	virtual void		removeObserver(Observer* observer) = 0;
	virtual void		addObserver(Observer* observer) = 0;

	//Other stuff
	//Car&		sendMutable(Car * car);
	//void		sendImmutable(const Car& car);
};

