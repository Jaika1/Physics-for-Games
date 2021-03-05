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
	/// Resolves a collision between this body and another by applying contact and rotational forces accordingly, all while dealing with penetration.
	/// </summary>
	/// <param name="actor2">The other object of which the interaction occured with.</param>
	/// <param name="contact">The point at which contact between this actor and <paramref name="actor2"/> was made.</param>
	/// <param name="collisionNormal">The normal vector for this collision between us and <paramref name="actor2"/>.</param>
	/// <param name="pen">The amount <paramref name="actor2"/> has penetrated into this actors surface.</param>
	void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr, float pen = 0);


	/// <summary>
	/// Used to retrieve the current position. Modifying this value will not change this objects position.
	/// </summary>
	/// <returns>The current positional vector.</returns>
	glm::vec2 getPosition() const { return m_position; }
	/// <summary>
	/// Used to set this objects position.
	/// </summary>
	/// <param name="position">The new position for this object.</param>
	void setPosition(glm::vec2 position) { m_position = position; };
	/// <summary>
	/// Retrieves whether or not this object is kinematic. Modifying the returned value will not change the actual value.
	/// </summary>
	/// <returns>A bool representing whether or not this object is kinematic.</returns>
	bool getKinematic() const { return m_isKinematic; }
	/// <summary>
	/// Used to set whether this object is kinematic or not.
	/// </summary>
	/// <param name="kinematic">True to become kinematic; otherwise false</param>
	void setKinematic(bool kinematic) { m_isKinematic = kinematic; };
	/// <summary>
	/// Used to retrieve the current velocity. Modifying this value will not change this objects velocity.
	/// </summary>
	/// <returns>The current velocity vector.</returns>
	glm::vec2 getVelocity() const { return m_velocity; }
	/// <summary>
	/// Used to retrieve the current angular velocity. Modifying this value will not change this objects angular velocity.
	/// </summary>
	/// <returns>The current angular velocity.</returns>
	float getAngularVelocity() const { return m_angularVelocity; }
	/// <summary>
	/// Used to retrieve the current rotation. Modifying this value will not change this objects rotation.
	/// </summary>
	/// <returns>This objects current rotation in radians.</returns>
	float getRotation() const { return m_rotation; }
	/// <summary>
	/// Used to retrieve this objects mass. Modifying this value will not change this objects mass.
	/// </summary>
	/// <returns>The mass of this object in newtons.</returns>
	float getMass() const { return m_isKinematic ? INT_MAX : m_mass; }
	/// <summary>
	/// Used to retrieve this objects moment of inertia. Modifying this value will not change this value.
	/// </summary>
	/// <returns>This objects moment of inertia.</returns>
	float getMoment() const { return m_isKinematic ? INT_MAX : m_moment; }
	/// <summary>
	/// Used to retrieve this objects linear drag. Modifying this value will not change the linear drag for this object.
	/// </summary>
	/// <returns>This objects linear drag.</returns>
	float getLinearDrag() const { return m_linearDrag; }
	/// <summary>
	/// Used to retrieve this objects angular drag. Modifying this value will not change the angular drag for this object.
	/// </summary>
	/// <returns>This objects angular drag.</returns>
	float getAngularDrag() const { return m_angularDrag; }
	/// <summary>
	/// Converts the given local-space position to world space.
	/// </summary>
	/// <param name="lpos">The position to convert from local to world space.</param>
	/// <returns>The given postition represented in world-space.</returns>
	glm::vec2 toWorld(glm::vec2 lpos) { return getPosition() + lpos; }

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
	/// <summary>
	/// This objects linear drag.
	/// </summary>
	float m_linearDrag;
	/// <summary>
	/// This objects angular drag.
	/// </summary>
	float m_angularDrag;
	/// <summary>
	/// Whether this object is static or not.
	/// </summary>
	float m_isKinematic;
};

