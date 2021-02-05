#include "Plane.h"
#include <Gizmos.h>

using namespace glm;

Plane::Plane(glm::vec2 normal, float distanceToOrigin, glm::vec4 colour) : PhysicsObject(PLANE), m_normal(normal), m_distanceToOrigin(distanceToOrigin), m_colour(colour)
{
	
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::draw()
{
	static float lineSegmentLength = 300;
	vec2 centerPoint = m_normal * m_distanceToOrigin;
	vec2 parallel(m_normal.y, -m_normal.x);
	vec4 colourFade = m_colour;
	colourFade.a = 0;
	vec2 start = centerPoint + (parallel * lineSegmentLength);
	vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DTri(start, end, start - m_normal * 3.0f, m_colour, m_colour, colourFade);
	aie::Gizmos::add2DTri(end, end - m_normal * 3.0f, start - m_normal * 3.0f, m_colour, colourFade, colourFade);
}

void Plane::resetPosition()
{
}
