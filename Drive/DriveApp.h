#pragma once

#include "Application.h"
#include "Renderer2D.h"

class Car;
class GUI;

class DriveApp : public aie::Application {
public:

	DriveApp();
	virtual ~DriveApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Car*				m_s13;
	//GUI*				m_gui;

	aie::Renderer2D*	m_2dRenderer;
};