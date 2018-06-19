#pragma once
#include "Observer.h"
#include <vector>

class Car;

class Subject
{
private:
	std::vector<Observer*> m_observers;

protected:
	void		notify(const Car& car);
	
public:
	//Subject();
	//~Subject();

	void		addObserver(Observer* observer);
	void		removeObserver(Observer* observer);

	//Other stuff
};

