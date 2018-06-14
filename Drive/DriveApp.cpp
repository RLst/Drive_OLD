#include "DriveApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

DriveApp::DriveApp() {

}

DriveApp::~DriveApp() {

}

bool DriveApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	////////////////////////////
	s13 = new Car("../bin/textures/Silvia.png");
	s13->setPosition(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f);
	///////////////////////////

	return true;
}

void DriveApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void DriveApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	///////////////////////////
	s13->update(deltaTime);
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
	// draw your stuff here!
	s13->draw(m_2dRenderer);
	/////////////////////////////////
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}