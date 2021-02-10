#pragma once
#include "RigidBody.h"

/// <summary>
/// A 2D box (or square) that can interract with other objects.
/// </summary>
class Box :
	public Rigidbody
{
public:
	/// <summary>
	/// Initialise a new box with an initial position, velocity, mass, rotation, dimensions, and colour.
	/// </summary>
	/// <param name="position">The position of this object.</param>
	/// <param name="velocity">The initial velocity vector for this object.</param>
	/// <param name="mass">The mass of this object in newtons.</param>
	/// <param name="rotation">The rotation of this object in radians.</param>
	/// <param name="colour">The colour of this box to use when rendering.</param>
	Box(glm::vec2 position, glm::vec2 velocity, float mass, float rotation, glm::vec2 dimensions, glm::vec4 colour);

protected:
	/// <summary>
	/// The width and height of this box.
	/// </summary>
	glm::vec2 m_dimensions;
	/// <summary>
	/// The colour to be used when drawing this sphere.
	/// </summary>
	glm::vec4 m_colour;
};

