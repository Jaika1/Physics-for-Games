#include "Plane.h"
#include <Gizmos.h>
#include "RigidBody.h"

using namespace glm;

Plane::Plane(glm::vec2 normal, float distanceToOrigin, glm::vec4 colour) : PhysicsObject(PLANE), m_normal(normal), m_distanceToOrigin(distanceToOrigin), m_colour(colour)
{
	// The code above simply sets this objects initial position, velocity and mass, sets the rotation to 0 since it's
	// redundant here, sets the objects ID to a sphere for later identification, and finally sets the radius and colour
	// to the given values.
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	// 無用。
}

void Plane::draw()
{
	static float lineSegmentLength = 300;
	vec2 centerPoint = m_normal * m_distanceToOrigin;
	vec2 parallel(m_normal.y, -m_normal.x);
	vec4 colourFade = m_colour;
	colourFade.a = 0;
	vec2 start = centerPoint + (parallel * lineSegmentLength);
	vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DTri(start, end, start - m_normal * 3.0f, m_colour, m_colour, colourFade);
	aie::Gizmos::add2DTri(end, end - m_normal * 3.0f, start - m_normal * 3.0f, m_colour, colourFade, colourFade);
}

void Plane::resolveCollision(Rigidbody* actor2)
{
	float elasticity = 1;
	float energy = glm::dot(-(1 + elasticity) * (actor2->getVelocity()), m_normal) / (1 / actor2->getMass());

	glm::vec2 force = m_normal * energy;

	// Get the total sum of the amount of kinetic energy storred by these 2 bodies and store it for
	// checking after force has been applied.
	float kePre = actor2->getKineticEnergy();

	actor2->applyForce(force);

	float kePost = actor2->getKineticEnergy();

	// Calculate the difference in kinetic energy from pre to post and check is the change is >1%, as
	// this could inform us we have a calculation error.
	float keDiff = fabsf(kePost - kePre);
	if (keDiff > fabsf(kePre) * 0.01f) {
		printf("Kinetic energy discrepancy is >1%!");
	}
}
