#pragma once

namespace aie {
	class Renderer2D;
}

class GUI 
{
private:
	Car*	m_subject;

public:
	GUI(Car* car);
	~GUI();

	//Car&	getMutable(Car* car) override;
	//void	getImmutable(const Car& car) override;

	void	startup(Car* car);
	void	update(float deltaTime);
	void	draw(/*aie::Renderer2D * renderer*/);

	//void	onNotify(Car& car) override;
};

