#include "PhysicsObject.h"
#include "Sphere.h"

collisionCheck_t PhysicsObject::collisionCheckFunctionArray[COLLISIONROWSIZE * COLLISIONROWSIZE] = 
{ 
	&PhysicsObject::plane2Plane, &PhysicsObject::plane2Sphere, &PhysicsObject::plane2Box,
	&PhysicsObject::sphere2Plane, &PhysicsObject::sphere2Sphere, &PhysicsObject::sphere2Box,
	&PhysicsObject::box2Plane, &PhysicsObject::box2Sphere, &PhysicsObject::box2Box
};

bool PhysicsObject::checkCollision(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Grabs an ID from each actor that allows us to know what kind of shape it is.
	ShapeType a1shape = actor1->m_shapeID;
	ShapeType a2shape = actor2->m_shapeID;

	// Call the appropriate function to handle checking for and managing a collision between the 2 different shapes.
	return collisionCheckFunctionArray[(a1shape * COLLISIONROWSIZE) + a2shape](actor1, actor2);
}

#pragma region Collision Check Functions

bool PhysicsObject::plane2Plane(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Planes are always static, so a collision between the 2 will never result in anything. This will also be the only collision function that doesnt check if the 2 actors are actually of the correct type.
	return false;
}

bool PhysicsObject::plane2Sphere(PhysicsObject* actor1, PhysicsObject* actor2)
{

}

bool PhysicsObject::plane2Box(PhysicsObject* actor1, PhysicsObject* actor2)
{

}


bool PhysicsObject::sphere2Plane(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Use plane2Sphere with the parameters reversed.
	return plane2Sphere(actor2, actor1);
}

bool PhysicsObject::sphere2Sphere(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Attempt to cast the actors into spheres
	Sphere* sphere1 = dynamic_cast<Sphere*>(actor1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(actor2);

	// If a cast was unsuccessful, it will be a nullptr. This if statement checks that for us.
	if (sphere1 && sphere2)
	{
		// Get the distance between the center points of both spheres...
		float sphereDist = glm::length(sphere2->getPosition() - sphere1->getPosition());
		// Get the sum of both spheres radii...
		float radiusSum = sphere1->getRadius() + sphere2->getRadius();
		// And check to see if their distance is equal to or less than the sum of their radii!
		return sphereDist <= radiusSum;
	}

	printf("sphere2Sphere collision function activated, but one or more are of the wrong type!\n");
	return false;
}

bool PhysicsObject::sphere2Box(PhysicsObject* actor1, PhysicsObject* actor2)
{

}


bool PhysicsObject::box2Plane(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Use plane2Box with the parameters reversed.
	return plane2Box(actor2, actor1);
}

bool PhysicsObject::box2Sphere(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Use sphere2Box with the parameters reversed.
	return sphere2Box(actor2, actor1);
}

bool PhysicsObject::box2Box(PhysicsObject* actor1, PhysicsObject* actor2)
{

}

#pragma endregion