#pragma once
#include "Observer.h"

namespace aie {
	class Renderer2D;
}

class GUI : public Observer
{
private:
	Car * m_carObserved;
public:
	GUI();
	~GUI();

	void	startup();
	void	update(float deltaTime);
	void	onNotify(const Car& car) override;
	void	draw(/*aie::Renderer2D * renderer*/);

};

