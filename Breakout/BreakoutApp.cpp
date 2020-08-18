#include "BreakoutApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm\ext.hpp>
#include <Gizmos.h>

BreakoutApp::BreakoutApp() 
{

}

BreakoutApp::~BreakoutApp() 
{

}

bool BreakoutApp::startup() 
{
	//Initlize the gizmos singleton class
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	//TODO: remember to change this when redistributing a build!
	//The following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void BreakoutApp::shutdown()
{

	delete m_font;
	delete m_2dRenderer;
}

void BreakoutApp::update(float deltaTime) 
{

	//Input example
	aie::Input* input = aie::Input::getInstance();

	//Exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BreakoutApp::draw() 
{

	//Wipe the screen to the background colour
	clearScreen();

	//Begin drawing sprites
	m_2dRenderer->begin();

	//Draw your stuff here!
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
					   -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	//Output some text, uses the last used color
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	//Done drawing sprites
	m_2dRenderer->end();
}