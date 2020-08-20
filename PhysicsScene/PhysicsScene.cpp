#include "PhysicsScene.h"
#include "RigidBody.h"
#include <list>

PhysicsScene::PhysicsScene() : m_timestep(0.01f), m_gravity(glm::vec2(0,0))
{
}

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
	//Create a list of objects for which we've checked collisions
	static std::list<PhysicsObject*> dirty;

	static float accumlatedTime = 0.0f;
	accumlatedTime += deltaTime;

	//While eniough tine has accumulated
	while (accumlatedTime >= m_timestep)
	{
		//For each PhysicsObject in m_actors
		for (auto pActor : m_actors)
		{
			//update physics of that object
			pActor->fixedUpdate(m_gravity, m_timestep);
		}

		//Spend time needed for that update
		accumlatedTime -= m_timestep;

		for (auto actor : m_actors)
		{
			for (auto other : m_actors)
			{
				//If we aren't checking an actor's collision with itself
				if (actor == other)
				{
					continue;
				}

				//If the actors haven't already been checked
				if (std::find(dirty.begin(), dirty.end(), actor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), actor) != dirty.end())
				{
					continue;
				}

				//If the actor and other are rigidbodies
				RigidBody* actorRB = dynamic_cast<RigidBody*>(actor);
				RigidBody* otherRB = dynamic_cast<RigidBody*>(other);

				if (!actorRB || !otherRB)
				{
					continue;
				}

				//Check the collision
				if (actorRB->checkCollision(other))
				{
					actorRB->applyForceToActor(otherRB, actorRB->getVelocity() *
											   actorRB->getMass());

					dirty.push_back(actorRB);
					dirty.push_back(otherRB);
				}
			}
		}

		dirty.clear();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	for (auto actor : m_actors)
	{
		actor->debug();
	}
}
