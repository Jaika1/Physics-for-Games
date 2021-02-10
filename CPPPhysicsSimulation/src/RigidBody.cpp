#include "RigidBody.h"
#include "PhysicsGame.h"
#include "PhysicsScene.h"

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
	// Apply the force of gravity (also in units/s), multiplied by this objects mass 
	applyForce(gravity * m_mass * timeStep);
	// Then, add the current velocity in units/s multiplied by the amount of time per step in seconds to the current position.
	m_position += m_velocity * timeStep;
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

void Rigidbody::resolveCollision(Rigidbody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->m_position - m_position);
	glm::vec2 relativeVelocity = actor2->m_velocity - m_velocity;

	float elasticity = 1;
	float energy = glm::dot(-(1+elasticity) * (relativeVelocity), normal) / ( (1 / m_mass) + (1 / actor2->m_mass));

	glm::vec2 force = normal * energy;

	// Get the total sum of the amount of kinetic energy storred by these 2 bodies and store it for
	// checking after force has been applied.
	float kePre = getKineticEnergy() + actor2->getKineticEnergy();

	applyForceToActor(actor2, force);

	float kePost = getKineticEnergy() + actor2->getKineticEnergy();

	// Calculate the difference in kinetic energy from pre to post and check is the change is >1%, as
	// this could inform us we have a calculation error.
	float keDiff = fabsf(kePost - kePre);
	if (keDiff > fabsf(kePre) * 0.01f) {
		printf("Kinetic energy discrepancy is >1%!");
	}
}

float Rigidbody::getKineticEnergy()
{
	// KE = (1/2)mv^2
	return 0.5f * (m_mass * powf(glm::length(m_velocity), 2));
}

float Rigidbody::getPotentialEnergy()
{
	// PE = -mgh
	return - m_mass * glm::dot(GameInstance->getScene().getGravity(), m_position);
}
