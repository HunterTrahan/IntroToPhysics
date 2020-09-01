#include "Plane.h"
#include <Gizmos.h>

Plane::Plane() : PhysicsObject(PLANE)
{
	m_normal = glm::vec2(0.0f, 0.0f);
	m_distanceToOrigin = 0.0f;
}

Plane::Plane(glm::vec2 normal, float distanceToOrigin) : PhysicsObject(PLANE)
{
	m_normal = normal;
	m_distanceToOrigin = distanceToOrigin;
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 color(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, color);
}
