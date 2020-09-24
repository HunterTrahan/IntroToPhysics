#pragma once
#include "Input.h"
#include "RigidBody.h"
#include "Application.h"
#include <iostream>

///
/// Handles The mouse functions
///
class MouseBehavior
{
	public:
		///
		/// Constructor for the class
		///
		MouseBehavior(float radius, aie::Application* application);

		///
		/// Find the mouse position
		///
		void update();

		///
		/// Set the ball to the mouses position
		///
		void onMouseCollison(RigidBody*);

		///
		/// Return the mouse position
		///
		glm::vec2 getMousePosition();

		///
		/// Return the collison radius
		///
		float getCollisonRadius();

	private:
		///
		/// refrence to the application
		///
		aie::Application* m_app;

		///
		/// stores the collison Radius
		///
		float m_collisionRadius;

		///
		/// stores the mouse position
		///
		glm::vec2 m_mousePos;
};

