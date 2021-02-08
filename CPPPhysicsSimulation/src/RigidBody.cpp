#include "RigidBody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID),
m_position(position), m_velocity(velocity), m_rotation(rotation), m_mass(mass)
{
	// The code above sets up this instance with an initial position, velocity, rotation and mass, along with
	// passing through shapeID to the inherited PhysicsObject.
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	// Add the current velocity in units/s multiplied by the amount of time per step in seconds to the current position.
	m_position += m_velocity * timeStep;
	// Then, apply the force of gravity (also in units/s), multiplied by this objects mass 
	applyForce(gravity * m_mass * timeStep);
}

void Rigidbody::applyForce(glm::vec2 force)
{
	// A = F/M
	m_velocity += force / m_mass;
}

void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force)
{
	// Apply a force to the other actor, then our own, due to newtons third law of motion. 
	actor2->applyForce(force);
	applyForce(-force);
}
