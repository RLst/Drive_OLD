#include "Subject.h"
#include "Car.h"

class Entity;
class Event {};

//Subject::Subject()
//{}
//
//Subject::~Subject()
//{}

void Subject::notify(const Car & car)
{
	for (int i = 0; i < m_observers.size(); i++) {
		m_observers[i]->onNotify(car);
	}
}

void Subject::addObserver(Observer * observer)
{
	m_observers.push_back(observer);
}

void Subject::removeObserver(Observer * observer)
{
	m_observers.pop_back();
}
