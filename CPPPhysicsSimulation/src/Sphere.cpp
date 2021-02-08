#include "Sphere.h"
#include <Gizmos.h>
#include <glm.hpp>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody(SPHERE, position, velocity, 0, mass), m_radius(radius), m_colour(colour)
{
	// The code above simply sets this objects initial position, velocity and mass, sets the rotation to 0 since it's
	// redundant here, sets the objects ID to a sphere for later identification, and finally sets the radius and colour
	// to the given values.
}

void Sphere::draw()
{
	// Simply adds the sphere to the render queue. 20 segments should be plenty for what we'll be drawing.
	aie::Gizmos::add2DCircle(m_position, m_radius, 20u, m_colour);
}
