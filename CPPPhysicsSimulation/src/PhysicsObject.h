#pragma once
#include <glm.hpp>

class PhysicsObject;

typedef bool (*collisionCheck_t)(PhysicsObject* actor1, PhysicsObject* actor2);

enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX,
	COLLISIONROWSIZE
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}
	ShapeType m_shapeID;

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {};
	static bool checkCollision(PhysicsObject* actor1, PhysicsObject* actor2);
private:
	static collisionCheck_t collisionCheckFunctionArray[];
	static bool sphere2Sphere(PhysicsObject* actor1, PhysicsObject* actor2);
};