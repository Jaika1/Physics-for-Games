#pragma once
#include "PhysicsObject.h"

/// <summary>
/// An expansion of the PhysicsObject class that adds all of the fundamentals of a non-static object such as position, velocity, rotation and mass. Similarly to PhysicsObject, this class is intended to be inherited, rather than instantiated as-is.
/// </summary>
class Rigidbody :
	public PhysicsObject
{
public:
	/// <summary>
	/// Creates a new Rigidbody with the given position, initial velocity, rotation and mass, along with passing through the shapeID to our inherited PhysicsObject
	/// </summary>
	/// <param name="shapeID">What type of shape this instance is.</param>
	/// <param name="position">The position of this object.</param>
	/// <param name="velocity">The initial velocity vector for this object.</param>
	/// <param name="rotation">The rotation of this object in radians.</param>
	/// <param name="mass">The mass of this object in newtons.</param>
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~Rigidbody();

	/// <summary>
	/// Overridden from PhysicsObject. Physics update, called when each fixed time-step has elapsed as defined in PhysicsScene.
	/// </summary>
	/// <param name="gravity">The gravity vector.</param>
	/// <param name="timeStep">The length of a time-step.</param>
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	/// <summary>
	/// Instantly applies a force to the object, accounting for its mass.
	/// </summary>
	/// <param name="force">A vector representing the force of which to add.</param>
	/// <param name="position">The position at which the collision occured.</param>
	void applyForce(glm::vec2 force, glm::vec2 position);
	/// <summary>
	/// Resolves a collision between this body and another.
	/// </summary>
	/// <param name="actor2">The other object of which the interaction occured with.</param>
	void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr); // FILL IN SUMMARY

	/// <summary>
	/// Used to retrieve the current position. Modifying this value will not change this objects position.
	/// </summary>
	/// <returns>The current positional vector.</returns>
	glm::vec2 getPosition() { return m_position; }
	/// <summary>
	/// Used to retrieve the current velocity. Modifying this value will not change this objects velocity.
	/// </summary>
	/// <returns>The current velocity vector.</returns>
	glm::vec2 getVelocity() { return m_velocity; }
	/// <summary>
	/// Used to retrieve the current rotation. Modifying this value will not change this objects rotation.
	/// </summary>
	/// <returns>This objects current rotation in radians.</returns>
	float getRotation() { return m_rotation; }
	/// <summary>
	/// Used to retrieve this objects mass. Modifying this value will not change this objects mass.
	/// </summary>
	/// <returns>The mass of this object in newtons.</returns>
	float getMass() { return m_mass; }
	/// <summary>
	/// Calculates and returns the kinetic energy exerted by this object.
	/// </summary>
	/// <returns>This objects kinetic energy in joules.</returns>
	float getKineticEnergy();
	/// <summary>
	/// Calculates and returns the potential energy of this object.
	/// </summary>
	/// <returns>This objects potential energy in joules.</returns>
	float getPotentialEnergy();


	/// <summary>
	/// Instantly applies a force to the desired object along with an equal and opposite force to the one this function is called from, accounting for both their masses.
	/// </summary>
	/// <param name="actor2">The object to apply a force to.</param>
	/// <param name="force">A vector representing the force of which to add.</param>
	[[depreciated("Pre-rotation function, use applyForce instead.")]]
	void applyForceToActor(Rigidbody* actor2, glm::vec2 force);

protected:
	/// <summary>
	/// The current position of this object.
	/// </summary>
	glm::vec2 m_position;
	/// <summary>
	/// This objects current velocity.
	/// </summary>
	glm::vec2 m_velocity;
	/// <summary>
	/// This objects current rotation.
	/// </summary>
	float m_rotation;
	/// <summary>
	/// This objects current angular velocity.
	/// </summary>
	float m_angularVelocity;
	/// <summary>
	/// This objects moment of inertia.
	/// </summary>
	float m_moment;
	/// <summary>
	/// The mass of this object.
	/// </summary>
	float m_mass;
};

