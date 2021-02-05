#include "Sphere.h"
#include <Gizmos.h>
#include <glm.hpp>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody(SPHERE, position, velocity, 0, mass), m_radius(radius), m_colour(colour)
{

}

void Sphere::draw()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour);
}
