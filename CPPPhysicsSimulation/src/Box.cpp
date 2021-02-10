#include "Box.h"

Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, float rotation, glm::vec2 dimensions, glm::vec4 colour) : Rigidbody(BOX, position, velocity, rotation, mass), m_dimensions(dimensions), m_color(colour)
{

}
