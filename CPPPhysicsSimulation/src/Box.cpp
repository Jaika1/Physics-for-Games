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
	aie::Gizmos::add2DLine(m_position, m_position + (m_localX * m_extents.x), glm::vec4(1 - m_colour.x, 1 - m_colour.y, 1 - m_colour.z, m_colour.a));
	aie::Gizmos::add2DLine(m_position, m_position + (m_localY * m_extents.y), glm::vec4(1 - m_colour.x, 1 - m_colour.y, 1 - m_colour.z, m_colour.a));
}

bool Box::checkBoxCorners(const Box& box, glm::vec2& contact, float& numContacts, float& pen, glm::vec2& edgeNormal)
{
	float minX, maxX, minY, maxY;
	float boxW = box.getExtents().x * 2;
	float boxH = box.getExtents().y * 2;
	float numLocalContacts = 0.0f;
	glm::vec2 localContact(0);
	bool first = true;

	for (float x = -box.getExtents().x; x < boxW; x += boxW)
	{
		for (float y = -box.getExtents().y; y < boxH; y += boxH)
		{
			glm::vec2 worldPos = box.getPosition() + x * box.m_localX + y * box.m_localY;
			glm::vec2 localPos(glm::dot(worldPos - m_position, m_localX), glm::dot(worldPos - m_position, m_localY));

			if (first || localPos.x < minX) minX = localPos.x;
			if (first || localPos.x > maxX) maxX = localPos.x;
			if (first || localPos.y < minY) minY = localPos.y;
			if (first || localPos.y > maxY) maxY = localPos.y;

			if (localPos.x >= -m_extents.x && localPos.x <= m_extents.x && localPos.y >= -m_extents.y && localPos.y <= m_extents.y)
			{
				numLocalContacts++;
				localContact = localPos;
			}

			first = false;
		}
	}

	if (maxX <= -m_extents.x || minX >= m_extents.x || maxY <= -m_extents.y || minY >= m_extents.y)
		return false;

	if (numLocalContacts == 0)
		return false;

	bool res = false;
	contact += m_position + (localContact.x * m_localX + localContact.y * m_localY) / numLocalContacts;
	numContacts++;

	float penetration = m_extents.x - minX;
	if (penetration > 0 && (penetration < pen || pen == 0)) 
	{ 
		edgeNormal = m_localX; 
		pen = penetration; 
		res = true; 
	}
	penetration = maxX + m_extents.x; 
	if (penetration > 0 && (penetration < pen || pen == 0)) 
	{ 
		edgeNormal = -m_localX; pen = penetration; res = true; 
	}
	penetration = m_extents.y - minY; 
	if (penetration > 0 && (penetration < pen || pen == 0)) 
	{ 
		edgeNormal = m_localY;
		pen = penetration;
		res = true; 
	}
	penetration = maxY + m_extents.y; 
	if (penetration > 0 && (penetration < pen || pen == 0)) 
	{ 
		edgeNormal = -m_localY; 
		pen = penetration;
		res = true;
	}return res;
}
