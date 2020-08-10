#include "DriveApp.h"
#include "Texture.h"
#include "Input.h"

#include "Car.h"
#include "GUI.h"

//Test matrix inv
#include <Matrix3.h>
#include "GameDefines.h"
#include <iostream>

DriveApp::DriveApp() {}

DriveApp::~DriveApp() {}

bool DriveApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	//m_2dRenderer->setCameraPos(getWindowWidth() * -0.5f, getWindowHeight() * -0.5f)
	////////////////////////////
	//Car
	m_s13 = new Car("../bin/textures/Silvia.png");
	m_s13->setPosition(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f);

	//RPM
	//m_gui = new GUI();

	/////////////////////////////////
	//test out matrix inverse
	//Matrix3 invMe;

	////Add in some raandom values
	//for (int i = 0; i < 3; ++i) {
	//	for (int j = 0; i < 3; ++j) {
	//		invMe.data[i][j] = (float)craprandom(0,500);
	//	}
	//}

	////Draw matrix before inverse
	//for (int i = 0; i < 3; ++i) {
	//	for (int j = 0; j < 3; ++j) {
	//		std::cout << invMe.data[i][j] << " , ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

	////Inverse
	//invMe.inverse();

	////Draw matrix after inverse
	//for (int i = 0; i < 3; ++i) {
	//	for (int j = 0; j < 3; ++j) {
	//		std::cout << invMe.data[i][j] << " , ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

	////Re-inverse
	//invMe.inverse();

	////Draw matrix after reverse
	//for (int i = 0; i < 3; ++i) {
	//	for (int j = 0; j < 3; ++j) {
	//		std::cout << invMe.data[i][j] << " , ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

	////Pause
	//std::cin.get();
	//////////////////////////////

	///////////////////////////

	return true;
}

void DriveApp::shutdown() {

	delete m_s13;
	//delete m_gui;
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
	//m_gui->draw(m_s13);
	/////////////////////////////////

	// done drawing sprites
	m_2dRenderer->end();
}