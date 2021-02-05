#include "PhysicsObject.h"
#include "Sphere.h"

collisionCheck_t PhysicsObject::collisionCheckFunctionArray[COLLISIONROWSIZE * COLLISIONROWSIZE] = 
{ 
	&PhysicsObject::sphere2Sphere, &PhysicsObject::sphere2Sphere, &PhysicsObject::sphere2Sphere,
	&PhysicsObject::sphere2Sphere, &PhysicsObject::sphere2Sphere, &PhysicsObject::sphere2Sphere,
	&PhysicsObject::sphere2Sphere, &PhysicsObject::sphere2Sphere, &PhysicsObject::sphere2Sphere
};

bool PhysicsObject::checkCollision(PhysicsObject* actor1, PhysicsObject* actor2)
{
	ShapeType a1shape = actor1->m_shapeID;
	ShapeType a2shape = actor2->m_shapeID;

	return collisionCheckFunctionArray[(a1shape * COLLISIONROWSIZE) + a2shape](actor1, actor2);
}

bool PhysicsObject::sphere2Sphere(PhysicsObject* actor1, PhysicsObject* actor2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(actor1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(actor2);

	if (sphere1 && sphere2)
	{
		float sphereDist = glm::length(sphere2->getPosition() - sphere1->getPosition());
		float radiusSum = sphere1->getRadius() + sphere2->getRadius();
		return sphereDist <= radiusSum;
	}

	printf("sphere2Sphere collision function activated, but one or more are of the wrong type!\n");
	return false;
}
