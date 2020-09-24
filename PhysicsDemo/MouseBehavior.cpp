#include "MouseBehavior.h"

// Initialize the radius and application
MouseBehavior::MouseBehavior(float radius, aie::Application* application)
{
	m_collisionRadius = radius;
	m_app = application;
}

// Find the mouse position
void MouseBehavior::update()
{
	aie::Input* input = aie::Input::getInstance();

	float windowWidth = m_app->getWindowWidth();
	float windowHeight = m_app->getWindowHeight();

	float mouseX = input->getMouseX() - windowWidth/2;
	float mouseY = input->getMouseY() - windowHeight/2;

	m_mousePos = { mouseX, mouseY };

	//std::cout << windowWidth << "," << windowHeight << std::endl;
}

// Set the ball to the mouses position
void MouseBehavior::onMouseCollison(RigidBody* ball)
{
	ball->setPosition(m_mousePos * 0.15f);
}

// Get the mouse position
glm::vec2 MouseBehavior::getMousePosition()
{
	return m_mousePos * 0.15f;
}

// Get the collison radius
float MouseBehavior::getCollisonRadius()
{
	return m_collisionRadius;
}
