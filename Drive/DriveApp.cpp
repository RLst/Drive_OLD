#include "DriveApp.h"
#include "Texture.h"
#include "Input.h"

#include "Car.h"
#include "GUI.h"

DriveApp::DriveApp() {}

DriveApp::~DriveApp() {}

bool DriveApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	////////////////////////////
	//Car
	m_s13 = new Car("../bin/textures/Silvia.png");
	m_s13->setPosition(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f);

	//RPM
	m_gui = new GUI();
	///////////////////////////

	return true;
}

void DriveApp::shutdown() {

	delete m_s13;
	delete m_gui;
	delete m_2dRenderer;
}

void DriveApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	///////////////////////////
	m_s13->update(deltaTime);
	/////////////////////////

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void DriveApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	///////////////////////////////
	//Car
	m_s13->draw(m_2dRenderer);

	//GUI
	m_gui->drawCarGUI(m_s13);
	/////////////////////////////////

	// done drawing sprites
	m_2dRenderer->end();
}