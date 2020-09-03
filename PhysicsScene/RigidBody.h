#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
	public:
		RigidBody(ShapeType shapeID, glm::vec2 position,
			glm::vec2 velocity, float rotation, float mass);
		~RigidBody() {}

		virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
		virtual void debug() {}

		void applyForce(glm::vec2 force);
		void applyForceToActor(RigidBody* otherActor, glm::vec2 force);

		virtual bool checkCollision(PhysicsObject* other) = 0;
		void resolveCollision(RigidBody* other);

		glm::vec2 getPosition() { return m_position; }
		glm::vec2 getVelocity() { return m_velocity; }
		float getRotation() { return m_rotation; }
		float getMass() { return m_mass; }

	protected:
		glm::vec2 m_position;
		glm::vec2 m_velocity;
		float m_rotation;
		float m_mass;
};