#pragma once
#include "PhysicsObject.h"

///
/// Class that defines what a rigidbody is
///
class RigidBody : public PhysicsObject
{
	public:
		///
		/// Constructor for the class
		///
		RigidBody(ShapeType shapeID, glm::vec2 position,
			glm::vec2 velocity, float rotation, float mass);

		///
		/// Deconstructor for the class
		///
		~RigidBody() {}

		///
		/// Updates gravity alongside angualr and linerar movement
		///
		virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

		///
		/// Calculates the change in velocity
		///
		void applyForce(glm::vec2 force, glm::vec2 position);

		///
		/// Checks for collison
		///
		virtual bool checkCollision(PhysicsObject* other) = 0;

		///
		/// Resolves collison between rigidbodies
		///
		void resolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

		///
		/// Returns the position
		///
		glm::vec2 getPosition() { return m_position; }

		///
		/// Returns the velocity
		///
		glm::vec2 getVelocity() { return m_velocity; }

		///
		/// Returns the mass
		///
		float getMass() { return m_mass; }

		///
		/// Returns the rotation
		///
		float getRotation() { return m_rotation; }

		///
		/// Returns the angular velocity
		///
		float getAngularVelocity() { return m_angularVelocity; }

		///
		/// Returns the movement
		///
		float getMoment() { return m_moment; }

		///
		/// Sets the position
		///
		void setPosition(glm::vec2 position) { m_position = position; }

		///
		/// Returns the linear drag
		///
		float getLinearDrag() { return m_linearDrag; }

		///
		/// Sets the linear drag
		///
		void setLinearDrag(float value) { m_linearDrag = value; }

		///
		/// Returns the angular drag
		///
		float getAngularDrag() { return m_angularDrag; }

		///
		/// Sets the angualr drag
		///
		void setAngularDrag(float value) { m_angularDrag = value; }

		///
		/// Returns the elasticty
		///
		float getElasticity() { return m_elasticity; }

		///
		/// Sets the elasticty
		///
		void setElasticity(float value) { m_elasticity = value; }


	protected:
		///
		/// Stores the position
		///
		glm::vec2 m_position;

		///
		/// Stores the velocity
		///
		glm::vec2 m_velocity;

		///
		/// Stores the mass
		///
		float m_mass;

		///
		/// Stores the rotation
		///
		float m_rotation;

		///
		/// Stores the angular velocity
		///
		float m_angularVelocity;

		///
		/// Stores the movement
		///
		float m_moment;

		///
		/// Stores the linear drag
		///
		float m_linearDrag = 0.3f;

		///
		/// Stores the angular drag
		///
		float m_angularDrag = 0.3f;

		///
		/// Store the elasticty
		///
		float m_elasticity = 0.5f;
};