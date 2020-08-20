#include "Sphere.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity,
	float mass, float radius, glm::vec4 color) :
	RigidBody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_color = color;
}

Sphere::~Sphere()
{
}
