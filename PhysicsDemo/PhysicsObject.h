#pragma once
#include "glm\ext.hpp"

///
/// Enumerator that contaisn PLANE, SPHERE, and SHAPE_COUNT
///
enum ShapeType
{
	PLANE = 0,
	SPHERE,
	SHAPE_COUNT
};

///
/// Class that handles all to do with physics objects
///
class PhysicsObject
{
	protected:
		///
		/// Constructor for the scene
		///
		PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}

	public:
		///
		/// Updates the gravity and timestep
		///
		virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;

		///
		/// Makes the gizmos
		///
		virtual void makeGizmo() = 0;

		///
		/// resets the position of an object
		///
		virtual void resetPosition() {};

		///
		/// returns the shapeID
		///
		ShapeType getShapeID() { return m_shapeID; }

	protected:
		///
		/// Stores the shapeID
		///
		ShapeType m_shapeID;
};