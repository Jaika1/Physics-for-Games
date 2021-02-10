#pragma once
#include "PhysicsObject.h"

class Rigidbody;

/// <summary>
/// A flat, infinitely long 2D surface that can interract with other objects.
/// </summary>
class Plane :
	public PhysicsObject
{
public:
	/// <summary>
	/// Initialise a new plane with a normal, distance from the origin, and colour.
	/// </summary>
	/// <param name="normal">The normal for this plane.</param>
	/// <param name="distanceToOrigin">The distance this plane is fron the origin.</param>
	/// <param name="colour">The colour of this plane to use when rendering.</param>
	Plane(glm::vec2 normal, float distanceToOrigin, glm::vec4 colour);

	/// <summary>
	/// Overridden from PhysicsObject. Physics update, called when each fixed time-step has elapsed as defined in PhysicsScene. Does nothing for planes.
	/// </summary>
	/// <param name="gravity">The gravity vector.</param>
	/// <param name="timeStep">The length of a time-step.</param>
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	/// <summary>
	/// Overridden from PhysicsObject. Queues the plane for drawing.
	/// </summary>
	virtual void draw();
	/// <summary>
	/// Resolves a collision between this body and another.
	/// </summary>
	/// <param name="actor2">The other object of which the interaction occured with.</param>
	void resolveCollision(Rigidbody* actor2);

	/// <summary>
	/// Used to retrieve the normal for this plane. Modifying this value will not change the normal.
	/// </summary>
	/// <returns>The normal vector for this plane.</returns>
	glm::vec2 getNormal() { return m_normal; }
	/// <summary>
	/// Used to retrieve the offset distance from the origin for this plane. Modifying this value will not change this offset.
	/// </summary>
	/// <returns>The offset distance from the origin for this plane.</returns>
	float getDistance() { return m_distanceToOrigin; }
	/// <summary>
	/// Used to retrieve this objects colour when drawing. Modifying this value will not change the colour of this object.
	/// </summary>
	/// <returns>The colour of which this object is represented with when drawn.</returns>
	glm::vec4 getColor() { return m_colour; }

protected:
	/// <summary>
	/// The normal for this plane.
	/// </summary>
	glm::vec2 m_normal;
	/// <summary>
	/// The colour to be used when drawing this sphere.
	/// </summary>
	glm::vec4 m_colour;
	/// <summary>
	/// The distance this object is from the origin.
	/// </summary>
	float m_distanceToOrigin;
};

