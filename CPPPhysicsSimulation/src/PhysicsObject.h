#pragma once
#include <glm.hpp>

class PhysicsObject
{
protected:
	PhysicsObject(){}
public:
	int ShapeID;
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {};
};