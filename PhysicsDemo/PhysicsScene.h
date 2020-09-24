#pragma once
#include "PhysicsObject.h"
#include "glm\ext.hpp"
#include "MouseBehavior.h"
#include <vector>

///
/// Class that handles the scene itself
///
class PhysicsScene
{
	public:
		///
		/// Constructor for the scene
		///
		PhysicsScene(MouseBehavior* mouseRef) : m_timeStep(0.01f), m_gravity(glm::vec2(0.0f, 0.0f)) { m_mouse = mouseRef; }

		///
		/// Deconstructor for the scene
		///
		~PhysicsScene();

		///
		/// Adds an actor the scene
		///
		void addActor(PhysicsObject* actor);

		///
		/// Removes an actor from the scene
		///
		void removeActor(PhysicsObject* actor);

		///
		/// Updates the scene
		///
		void update(float deltaTime);

		///
		/// Updates gizmos
		///
		void updateGizmos();

		///
		/// Checks for mouse collison
		///
		bool checkMouseCollision();

		///
		/// Sets the scenes gravity
		///
		void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }

		///
		/// Returns the scenes gravity
		///
		glm::vec2 getGravity() const { return m_gravity; }

		///
		/// Sets the timestep
		///
		void setTimeStep(const float timeStep) { m_timeStep = timeStep; }

		///
		/// Retrun the scenes gravity
		///
		float getTimeStep() const { return m_timeStep; }

		///
		/// CHeck for collision
		///
		void checkForCollision();

		///
		/// Plane to plane collision
		///
		static bool planeToPlane(PhysicsObject*, PhysicsObject*);

		///
		/// Plane to sphere collision
		///
		static bool planeToSphere(PhysicsObject*, PhysicsObject*);

		///
		/// Sphere to plane collision
		///
		static bool sphereToPlane(PhysicsObject*, PhysicsObject*);

		///
		/// Sphere to sphere collision
		///
		static bool sphereToSphere(PhysicsObject*, PhysicsObject*);

	protected:
		///
		/// Stores the gravity
		///
		glm::vec2	m_gravity;

		///
		/// Stores the timestep
		///
		float		m_timeStep;

		///
		/// Refrence to the mouse
		///
		MouseBehavior* m_mouse;

		///
		/// Refrence to the actors
		///
		std::vector<PhysicsObject*>	m_actors;
};