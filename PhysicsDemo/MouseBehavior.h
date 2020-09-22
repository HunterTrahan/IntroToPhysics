#pragma once
#include "Input.h"
#include "RigidBody.h"
#include "Application.h"
#include <iostream>

class MouseBehavior
{
	public:
		MouseBehavior(float radius, aie::Application* application);

		void update();
		void onMouseCollison(RigidBody*);
		glm::vec2 getMousePosition();
		float getCollisonRadius();

	private:
		aie::Application* m_app;
		float m_collisionRadius;
		glm::vec2 m_mousePos;
};

