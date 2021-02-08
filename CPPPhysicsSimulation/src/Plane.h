#pragma once
#include "PhysicsObject.h"

/// <summary>
/// A flat, infinitely long 2D surface that can interract with other objects.
/// </summary>
class Plane :
	public PhysicsObject
{
public:
	Plane(glm::vec2 normal, float distanceToOrigin, glm::vec4 colour);

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void draw();
	virtual void resetPosition();

	glm::vec2 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

protected:
	glm::vec2 m_normal;
	glm::vec4 m_colour;
	float m_distanceToOrigin;
};

