#include "PhysicsScene.h"

PhysicsScene::PhysicsScene() : m_timestep(0.01f), m_gravity(glm::vec2(0,0))
{
}

PhysicsScene::~PhysicsScene()
{
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
	//Update the physics at a fixed timestep

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
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}
