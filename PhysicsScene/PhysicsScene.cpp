#include "PhysicsScene.h"
#include "RigidBody.h"
#include <list>

PhysicsScene::~PhysicsScene()
{
	for (auto actor : m_actors) 
	{
		delete actor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	for (auto i = m_actors.begin(); i < m_actors.end(); i++) 
	{
		if (*i == actor) 
		{
			m_actors.erase(i);
		}
	}
}

void PhysicsScene::update(float deltaTime)
{
	// create a list of objects for which we've checked collisions
	static std::list<PhysicsObject*> dirty;

	// store how much time has accumulated since last update
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	// while enough time has accumulated...
	while (accumulatedTime >= m_timeStep)
	{
		// for each PhysicsObject in m_actors...
		for (auto pActor : m_actors) 
		{
			// updated the physics of that object
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		// spend the time needed for that update
		accumulatedTime -= m_timeStep;

		// for every combination of actors...
		for (auto actor : m_actors) 
		{
			for (auto other : m_actors) 
			{
				// if we aren't checking an actor's collision with itself
				if (actor == other)
					continue;

				// if the actors haven't already been checked
				if (std::find(dirty.begin(), dirty.end(), actor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), other) != dirty.end())
					continue;

				// if the actor and other are RigidBodies
				RigidBody* actorRB = dynamic_cast<RigidBody*>(actor);
				RigidBody* otherRB = dynamic_cast<RigidBody*>(other);
				if (!actorRB || !otherRB)
					continue;

				// check the collision
				if (actorRB->checkCollision(otherRB)) 
				{
					// apply the force of the collision
					actorRB->applyForceToActor(otherRB, actorRB->getVelocity() * actorRB->getMass());
					// add each actor to the dirty list
					dirty.push_back(actor);
					dirty.push_back(other);
				}
			}
		}
		dirty.clear();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	for (auto actor : m_actors) {
		actor->debug();
	}
}