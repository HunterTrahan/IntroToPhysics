#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

///
/// Class that handles all to do with displaying the scene
///
class PhysicsDemoApp : public aie::Application 
{
	public:

		///
		/// Constructor for the class
		///
		PhysicsDemoApp();

		///
		/// Deconstructor for the class
		///
		virtual ~PhysicsDemoApp();

		///
		/// On start up do the following
		///
		virtual bool startup();

		///
		/// On shutdown delete the following
		///
		virtual void shutdown();

		///
		/// Update the scene
		///
		virtual void update(float deltaTime);

		///
		/// Draw to the screen
		///
		virtual void draw();

		///
		/// Find the initial velocity
		///
		glm::vec2 calculateVelocity(glm::vec2 initialPosition, glm::vec2 finalPosition, float gravity, float time);

	protected:
		///
		/// Refrence to the 2D renderer
		///
		aie::Renderer2D* m_2dRenderer;
		
		///
		/// Refrence to the font
		///
		aie::Font* m_font;

		///
		/// Refrence to thr physics scene
		///
		PhysicsScene* m_physicsScene;

		///
		/// refrence to the mosue
		///
		MouseBehavior* m_mouse;
};