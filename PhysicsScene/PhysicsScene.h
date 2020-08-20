#pragma once
#include <glm\ext.hpp>
#include "PhysicsObject.h"
#include <vector>

class PhysicsScene
{
	public:
		PhysicsScene();
		~PhysicsScene();

		void addActor(PhysicsObject* actor);
		void removeActor(PhysicsObject* actor);
		void update(float deltaTime);
		void updateGizmos();

		void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
		glm::vec2 getGravity() const { return m_gravity; }

		void setTimestep(const float timestep) { m_timestep = timestep; }
		float getTimestep() const { return m_timestep; }

	protected:
		glm::vec2 m_gravity;
		float m_timestep;
		
		std::vector<PhysicsObject*> m_actors;
};

