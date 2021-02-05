#pragma once
#include "PhysicsObject.h"
class Plane :
	public PhysicsObject
{
public:
	glm::vec2 Normal;
	float OriginDistance;
};

