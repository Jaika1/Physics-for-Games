#pragma once
#include "RigidBody.h"

/// <summary>
/// A 2D sphere (or circle) that can interract with other objects.
/// </summary>
class Sphere :
	public Rigidbody
{
public:
	/// <summary>
	/// Initialise the new sphere with a position, initial velocity and mass, along with the spheres radius and colour.
	/// </summary>
	/// <param name="position">The position of this object.</param>
	/// <param name="velocity">The initial velocity vector for this object.</param>
	/// <param name="mass">The mass of this object in newtons.</param>
	/// <param name="radius">The radius of this sphere.</param>
	/// <param name="colour">The colour of this sphere to use when rendering.</param>
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);

	/// <summary>
	/// Overridden from PhysicsObject. Queues the sphere for drawing.
	/// </summary>
	virtual void draw();

	/// <summary>
	/// Used to retrieve this spheres radius. Modifying this value will not change this objects radius.
	/// </summary>
	/// <returns>this sphere's radius in units.</returns>
	float getRadius() { return m_radius; }
	/// <summary>
	/// Used to retrieve this objects colour when drawing. Modifying this value will not change the colour of this object.
	/// </summary>
	/// <returns>The colour of which this object is represented with when drawn.</returns>
	glm::vec4 getColor() { return m_colour; }

protected:
	/// <summary>
	/// The radius of this sphere in units.
	/// </summary>
	float m_radius;
	/// <summary>
	/// The colour to be used when drawing this sphere.
	/// </summary>
	glm::vec4 m_colour;
};

