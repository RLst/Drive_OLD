#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Car.h"

class DriveApp : public aie::Application {
public:

	DriveApp();
	virtual ~DriveApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Car*				s13;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};