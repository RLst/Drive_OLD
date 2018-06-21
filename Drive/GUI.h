#pragma once

namespace aie {
	class Renderer2D;
}

class Car;

class GUI 
{
private:
	//Car*	m_subject;

public:
	//GUI();
	//GUI(Car* car);
	//~GUI();

	////Car&	getMutable(Car* car) override;
	////void	getImmutable(const Car& car) override;

	//void	startup(Car* car);
	//void	update(float deltaTime);
	void	drawCarGUI(Car* car);

	//void	onNotify(Car& car) override;
};

