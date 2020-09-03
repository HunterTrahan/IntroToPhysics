#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
	: PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	//Apply gravity
	applyForce(gravity * m_mass * timeStep);
	//Calculate drag
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	if (glm::length(m_velocity) < 0.01f)
		m_velocity = glm::vec2(0.0f, 0.0f);
	if (glm::abs(m_angularVelocity) < 0.01f)
		m_angularVelocity = 0;
	//Calculate the change in position
	m_position += m_velocity * timeStep;
}

void RigidBody::applyForce(glm::vec2 force)
{
	//Calculate the change in velocity
	m_velocity += force / m_mass;
}

void RigidBody::applyForceToActor(RigidBody* otherActor, glm::vec2 force)
{
	//Apply the force to the other actor
	otherActor->applyForce(force);
	//Apply the opposite force to this actor
	applyForce(-force);
}

void RigidBody::resolveCollision(RigidBody* other)
{
	glm::vec2 collisionNormal = glm::normalize(other->getPosition() - m_position);
	glm::vec2 relativeVelocity = other->getVelocity() - m_velocity;

	float elasticity = (m_elasticity + other->getElasticity()) / 2;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), collisionNormal) /
		glm::dot(collisionNormal, collisionNormal * ((1 / m_mass) + (1 / other->getMass())));

	glm::vec2 force = collisionNormal * j;

	applyForceToActor(other, force);
}