#pragma once
#include "RigidBody.h"

///
/// Class that handles what it is to be a sphere
///
class Sphere : public RigidBody
{
	public:
		///
		/// Constructor for the sphere
		///
		Sphere(glm::vec2 position, glm::vec2 velocity,
			float mass, float radius, glm::vec4 color);

		///
		/// Deconstructor for the sphere
		///
		~Sphere() {}

		///
		/// Creates a gizmo
		///
		virtual void makeGizmo();

		///
		/// Checks for collision
		///
		virtual bool checkCollision(PhysicsObject* other);

		///
		/// Returns the radius
		///
		float getRadius() { return m_radius; }

		///
		/// Returns the color
		///
		glm::vec4 getColor() { return m_color; }

	protected:
		///
		/// Stores the radius
		///
		float m_radius;

		///
		/// Stores the color
		///
		glm::vec4 m_color;
};