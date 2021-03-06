#include "RigidBody.h"
#include "PhysicsGame.h"
#include "PhysicsScene.h"

#define MIN_LINEAR_THRESHOLD 0.01f
#define MIN_ANGULAR_THRESHOLD MIN_LINEAR_THRESHOLD

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID),
m_position(position), m_velocity(velocity), m_rotation(rotation), m_mass(mass), m_angularVelocity(0.0f), m_linearDrag(1.0f), m_angularDrag(1.0f), m_isKinematic(false)
{
	// The code above sets up this instance with an initial position, velocity, rotation and mass, along with
	// passing through shapeID to the inherited PhysicsObject.
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	if (m_isKinematic) 
	{
		m_velocity = glm::vec2(0);
		m_angularVelocity = 0.0f;
		return;
	}

	// Apply the force of gravity (also in units/s), multiplied by this objects mass 
	applyForce(gravity * m_mass * timeStep, glm::vec2(0));

	// Calculate and apply drag to each velocity variable
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD && length(m_velocity) < length(gravity) * m_linearDrag * timeStep) m_velocity = glm::vec2(0.0f);
	if (fabsf(m_angularVelocity) < MIN_ANGULAR_THRESHOLD) m_angularVelocity = 0.0f;

	// Then, add the current velocity in units/s multiplied by the amount of time per step in seconds to the current position.
	m_position += m_velocity * timeStep;

	m_rotation += m_angularVelocity * timeStep;
}

void Rigidbody::applyForce(glm::vec2 force, glm::vec2 position)
{
	// A = F/M
	m_velocity += force / getMass();
	m_angularVelocity += (force.y * position.x - force.x * position.y) / getMoment();
}

void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force)
{
	// Apply a force to the other actor, then our own, due to newtons third law of motion. 
	actor2->applyForce(force, glm::vec2(0));
	applyForce(-force, glm::vec2(0));
}

void Rigidbody::resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal, float pen)
{
	// Find the vector between their centres, or use the provided direction of force and make sure
	// it's normalised before proceeding.
	glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal : actor2->m_position - m_position);
	// Get the vector perpendicular to the normal
	glm::vec2 perp(normal.y, -normal.x);

	// 'r' is defined as the radius from axis to application of force
	float r1 = glm::dot(contact - m_position, -perp);
	float r2 = glm::dot(contact - actor2->m_position, perp);
	// Velocities of the contact points on this object and the other actor.
	float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
	float v2 = glm::dot(actor2->m_velocity, normal) + r2 * actor2->m_angularVelocity;

	// Check to see if they are actually moving closer
	if (v1 > v2)
	{
		float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
		float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2 * r2) / actor2->m_moment);

		float elasticity = (getElasticity() + actor2->getElasticity()) / 2.0f;

		glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;


#if _DEBUG
		// Get the total sum of the amount of kinetic energy storred by these 2 bodies and store it for
		// checking after force has been applied.
		float kePre = getKineticEnergy() + actor2->getKineticEnergy();
#endif

		//Apply equal and opposite forces
		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->m_position);

#if _DEBUG
		float kePost = getKineticEnergy() + actor2->getKineticEnergy();

		// Calculate the difference in kinetic energy from pre to post and check is the change is >1%, as
		// this could inform us we have a calculation error.
		float keDiff = fabsf(kePost - kePre);
		if (keDiff > fabsf(kePre) * 0.01f) {
			printf("Kinetic energy discrepancy is >1%! (Rigidbody resolve)\n\r");
		}
#endif

		if (pen > 0)
		{
			GameInstance->getScene()->ApplyContactForces(this, actor2, normal, pen);
		}
	}
}

float Rigidbody::getKineticEnergy()
{
	// KE = (1/2)mv^2
	return 0.5f * (m_mass * glm::dot(m_velocity, m_velocity) + m_moment * m_angularVelocity * m_angularVelocity);
}

float Rigidbody::getPotentialEnergy()
{
	// PE = -mgh
	return - m_mass * glm::dot(GameInstance->getScene()->getGravity(), m_position);
}
