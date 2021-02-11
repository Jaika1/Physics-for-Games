#include "Box.h"
#include <Gizmos.h>

Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, float rotation, glm::vec2 dimensions, glm::vec4 colour) : Rigidbody(BOX, position, velocity, rotation, mass), m_extents(dimensions), m_colour(colour), m_localX(glm::vec2(1, 0)), m_localY(glm::vec2(0, 1))
{
	m_moment = 1.0f / 12.0f * mass * dimensions.x * dimensions.y;
}

void Box::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	Rigidbody::fixedUpdate(gravity, timeStep);

	float cos = cosf(m_rotation);
	float sin = sinf(m_rotation);

	// This is essentially rotation-matrix logic
	m_localX = glm::normalize(glm::vec2(cos, sin));
	m_localY = glm::normalize(glm::vec2(-sin, cos));
}

void Box::draw()
{
	// Draw using local axes
	glm::vec2 topLeftCorner     = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
	glm::vec2 topRightCorner    = m_position + m_localX * m_extents.x + m_localY * m_extents.y;
	glm::vec2 bottomLeftCorner  = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 bottomRightCorner = m_position + m_localX * m_extents.x - m_localY * m_extents.y;

	aie::Gizmos::add2DTri(topLeftCorner, bottomRightCorner, topRightCorner, m_colour);
	aie::Gizmos::add2DTri(topLeftCorner, bottomLeftCorner, bottomRightCorner, m_colour);

	// Draw a line to represent each local axis
	aie::Gizmos::add2DLine(m_position, m_position + (m_localX * m_extents.x), -m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + (m_localY * m_extents.y), -m_colour);
}
