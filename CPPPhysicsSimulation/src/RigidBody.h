#pragma once
#include "PhysicsObject.h"
class RigidBody :
	public PhysicsObject
{
public:
	glm::vec2 Position;
	glm::vec2 Velcoity;
	float Rotation;
	float Mass;

	void applyForce(glm::vec2 force);
};

