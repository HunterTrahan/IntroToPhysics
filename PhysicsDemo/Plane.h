#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"

///
/// Class that handles what it is to be a plane
///
class Plane : public PhysicsObject
{
	public:
		///
		/// Default constructor for the class
		///
		Plane();

		///
		/// Moddified constructor for the class
		///
		Plane(glm::vec2 normal, float distanceToOrigin);

		///
		/// Deconstructor for the class
		///
		~Plane() {}

		///
		/// Updates the gravity and timestep
		///
		virtual void fixedUpdate(glm::vec2 gravity, float timeStep) {}

		///
		/// Makes gizmos
		///
		virtual void makeGizmo();

		///
		/// Resolves collision between this plane and another object
		///
		void resolveCollision(RigidBody* other, glm::vec2 contact);

		///
		/// Returns the normal
		///
		glm::vec2 getNormal() { return m_normal; }

		///
		/// Returns the distance to origin
		///
		float getDistance() { return m_distanceToOrigin; }

	protected:
		///
		/// Stores the normal value
		///
		glm::vec2 m_normal;

		///
		/// Stores the distance to origin value
		///
		float m_distanceToOrigin;
};