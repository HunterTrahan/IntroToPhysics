#pragma once
#include "PhysicsObject.h"
#include "glm\ext.hpp"
#include "MouseBehavior.h"
#include <vector>

class PhysicsScene
{
	public:
		PhysicsScene(MouseBehavior* mouseRef) : m_timeStep(0.01f), m_gravity(glm::vec2(0.0f, 0.0f)) { mouse = mouseRef; }
		~PhysicsScene();

		void addActor(PhysicsObject* actor);
		void removeActor(PhysicsObject* actor);
		void update(float deltaTime);
		void updateGizmos();
		void debugScene();
		bool checkMouseCollision();

		void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
		glm::vec2 getGravity() const { return m_gravity; }

		void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
		float getTimeStep() const { return m_timeStep; }

		void checkForCollision();

		static bool planeToPlane(PhysicsObject*, PhysicsObject*);
		static bool planeToSphere(PhysicsObject*, PhysicsObject*);
		static bool sphereToPlane(PhysicsObject*, PhysicsObject*);
		static bool sphereToSphere(PhysicsObject*, PhysicsObject*);

	protected:
		glm::vec2	m_gravity;
		float		m_timeStep;
		MouseBehavior* mouse;

		std::vector<PhysicsObject*>	m_actors;
};