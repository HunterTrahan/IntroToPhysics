#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include <Gizmos.h>
#include <list>

PhysicsScene::~PhysicsScene()
{
	for (auto actor : m_actors)
	{
		delete actor;
	}
}

// Add actors to the scene
void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

// Remove actors from the scene
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

// Update the scene
void PhysicsScene::update(float deltaTime)
{
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
		// check for collisions
		checkForCollision();
	}
	m_mouse->update();
}

// Update Gizmos
void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

// Check for mouse collision 
bool PhysicsScene::checkMouseCollision()
{
	//aie::Gizmos::add2DCircle(mouse->getMousePosition(), mouse->getCollisonRadius(), 10, {8,8,0,3});
	std::cout << m_mouse->getMousePosition().x << "," << m_mouse->getMousePosition().y << std::endl;
	Sphere* sphere = nullptr;
	for (int i = 0; i < m_actors.size(); i++)
	{
		sphere = dynamic_cast<Sphere*>(m_actors[i]);
		if (m_mouse != nullptr && sphere != nullptr)
		{
			// check collision
			if (glm::distance(m_mouse->getMousePosition(), sphere->getPosition()) < m_mouse->getCollisonRadius() + sphere->getRadius())
			{
				m_mouse->onMouseCollison(sphere);
				return true;
			}
		}
	}
	return false;
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);


// Holds the collision functions
static fn collisionFunctions[] =
{
	PhysicsScene::planeToPlane, PhysicsScene::planeToSphere,
	PhysicsScene::sphereToPlane, PhysicsScene::sphereToSphere
};

// Check for collision
void PhysicsScene::checkForCollision()
{
	// get the number of actors in the scene
	int actorCount = m_actors.size();

	// check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{

		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			// find the function in the collision function array
			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPtr = collisionFunctions[functionID];
			if (collisionFunctionPtr != nullptr)
			{
				// check collision
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

// Plane to Plane collision
bool PhysicsScene::planeToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Plane* plane1 = dynamic_cast<Plane*>(object1);
	Plane* plane2 = dynamic_cast<Plane*>(object2);
	if (plane1 != nullptr && plane2 != nullptr)
	{
		if (plane1->getNormal().x != plane2->getNormal().x || plane1->getNormal().y != plane2->getNormal().y)
		{
			return true;
		}
	}
	return false;
}

// Plane to Sphere collision
bool PhysicsScene::planeToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	sphereToPlane(object2, object1);
	return false;
}

// Plane to Sphere Collision
bool PhysicsScene::sphereToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);
	if (sphere != nullptr && plane != nullptr)
	{
		// calculate distance from sphere surface to plane surface
		float sphereToPlaneDistance =
			glm::dot(sphere->getPosition(), plane->getNormal())
			- plane->getDistance();
		// flip the normal if behind the plane
		glm::vec2 collisionNormal = plane->getNormal();
		if (sphereToPlaneDistance < 0)
		{
			collisionNormal *= -1;
			sphereToPlaneDistance *= -1;
		}
		// check collision
		sphereToPlaneDistance -= sphere->getRadius();
		if (sphereToPlaneDistance <= 0)
		{
			// resolve collision
			glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
			plane->resolveCollision(sphere, contact);
			return true;
		}
	}
	return false;
}

// Sphere to Sphere Collision
bool PhysicsScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		// check collision
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius())
		{
			// resolve collision
			glm::vec2 contact = (sphere1->getPosition() + sphere2->getPosition()) * 0.5f;
			sphere1->resolveCollision(sphere2, contact);
			return true;
		}
	}
	return false;
}