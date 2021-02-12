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
	/// Initialise a new box with an initial position, velocity, mass, rotation, extents, and colour.
	/// </summary>
	/// <param name="position">The position of this object.</param>
	/// <param name="velocity">The initial velocity vector for this object.</param>
	/// <param name="mass">The mass of this object in newtons.</param>
	/// <param name="rotation">The rotation of this object in radians.</param>
	/// <param name="extents">The extents of this box from the center of mass.</param>
	/// <param name="colour">The colour of this box to use when rendering.</param>
	Box(glm::vec2 position, glm::vec2 velocity, float mass, float rotation, glm::vec2 extents, glm::vec4 colour);

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) override;
	virtual void draw() override;

	bool checkBoxCorners(const Box& box, glm::vec2& contact, float& numContacts, float& pen, glm::vec2& edgeNormal);

	/// <summary>
	/// Used to retrieve the extents of tis box. Modifying this value will not change the value of either extent.
	/// </summary>
	/// <returns>The extents of this box.</returns>
	glm::vec2 getExtents() const { return m_extents; }
	/// <summary>
	/// Used to retrieve this objects colour when drawing. Modifying this value will not change the colour of this object.
	/// </summary>
	/// <returns>The colour of which this object is represented with when drawn.</returns>
	glm::vec4 getColor() const { return m_colour; }
	/// <summary>
	/// Used to retrieve the local x axis. Modifying this value will not change the axis.
	/// </summary>
	/// <returns>The local x axis relative to this objects center of mass</returns>
	glm::vec2 getLocalX() const { return m_localX; }
	/// <summary>
	/// Used to retrieve the local y axis. Modifying this value will not change the axis.
	/// </summary>
	/// <returns>The local y axis relative to this objects center of mass</returns>
	glm::vec2 getLocalY() const { return m_localY; }

protected:
	/// <summary>
	/// The width and height of this box.
	/// </summary>
	glm::vec2 m_extents;
	/// <summary>
	/// The colour to be used when drawing this sphere.
	/// </summary>
	glm::vec4 m_colour;
	/// <summary>
	/// The local X axis for this box.
	/// </summary>
	glm::vec2 m_localX;
	/// <summary>
	/// The local Y axis for this box.
	/// </summary>
	glm::vec2 m_localY;
};

