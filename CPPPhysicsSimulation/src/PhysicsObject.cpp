#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

collisionCheck_t PhysicsObject::collisionCheckFunctionArray[SHAPE_COUNT * SHAPE_COUNT] = 
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

	if (a1shape < 0 || a2shape < 0) return false;

	// Call the appropriate function to handle checking for and managing a collision between the 2 different shapes.
	return collisionCheckFunctionArray[(a1shape * SHAPE_COUNT) + a2shape](actor1, actor2);
}

#pragma region Collision Check Functions

bool PhysicsObject::plane2Plane(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Planes are always static, so a collision between the 2 will never result in anything. This will also be the only collision function that doesnt check if the 2 actors are actually of the correct type.
	return false;
}

bool PhysicsObject::plane2Sphere(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Attempt to cast the actors into a plane and a sphere.
	Plane* plane = dynamic_cast<Plane*>(actor1);
	Sphere* sphere = dynamic_cast<Sphere*>(actor2);

	// If a cast was unsuccessful, it will be a nullptr. This if statement checks that for us.
	if (plane && sphere)
	{
		// D1 = (C * N) - D - R
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();
		float intersection = sphere->getRadius() - sphereToPlane;
		float velocityOutOfPlane = glm::dot(sphere->getVelocity(), plane->getNormal());

		if (intersection > 0 && velocityOutOfPlane < 0) {
			// handle collision

			glm::vec2 pointOfContact = (plane->getNormal() * sphere->getRadius());
			plane->resolveCollision(sphere, sphere->getPosition() - pointOfContact);
			return true;
		}
		return false;
	}

	printf("plane2Sphere collision function activated, but one or more are of the wrong type!\n");
	return false;
}

bool PhysicsObject::plane2Box(PhysicsObject* actor1, PhysicsObject* actor2)
{
	// Attempt to cast the actors into a plane and a box.
	Plane* plane = dynamic_cast<Plane*>(actor1);
	Box* box = dynamic_cast<Box*>(actor2);

	// If a cast was unsuccessful, it will be a nullptr. This if statement checks that for us.
	if (plane && box)
	{
		float numContacts = 0;
		glm::vec2 contact(0.0f);
		float contactV = 0.0f;

		// Aquire a representitive point on the plane
		glm::vec2 planeOrigin = plane->getNormal() * plane->getDistance();

		//Check for a collision at each corner of our box
		for (float x = -box->getExtents().x; x < box->getExtents().x * 2.0f; x += box->getExtents().x * 2.0f)
		{
			for (float y = -box->getExtents().y; y < box->getExtents().y * 2.0f; y += box->getExtents().y * 2.0f)
			{
				glm::vec2 cornerPosition = box->getPosition() + x * box->getLocalX() + y * box->getLocalY();
				float distanceFromPlane = glm::dot(cornerPosition - planeOrigin, plane->getNormal());

				glm::vec2 displacement = x * box->getLocalX() + y * box->getLocalY();
				glm::vec2 pointVelocity = box->getVelocity() + box->getAngularVelocity() * glm::vec2(-displacement.y, displacement.x);
				float velocityIntoPlane = glm::dot(pointVelocity, plane->getNormal());

				if (distanceFromPlane < 0.0f && velocityIntoPlane <= 0.0f)
				{
					++numContacts;
					contact += cornerPosition;
					contactV += velocityIntoPlane;
				}
			}
		}

		if (numContacts)
		{
			plane->resolveCollision(box, contact / numContacts);
			return true;
		}
		return false;
	}

	printf("plane2Box collision function activated, but one or more are of the wrong type!\n");
	return false;
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
		float penetration = sphere1->getRadius() + sphere2->getRadius() - sphereDist;
		// And check to see if their distance is equal to or less than the sum of their radii!
		if (penetration > 0) {
			sphere1->resolveCollision(sphere2, 0.5f * (sphere1->getPosition() + sphere2->getPosition()), nullptr, penetration);
			return true;
		}
		return false;
	}

	printf("sphere2Sphere collision function activated, but one or more are of the wrong type!\n");
	return false;
}

bool PhysicsObject::sphere2Box(PhysicsObject* actor1, PhysicsObject* actor2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(actor1);
	Box* box = dynamic_cast<Box*>(actor2);

	if (sphere && box)
	{
		glm::vec2 circlePosWorld = sphere->getPosition() - box->getPosition();
		glm::vec2 circlePosBox = glm::vec2(glm::dot(circlePosWorld, box->getLocalX()), glm::dot(circlePosWorld, box->getLocalY()));

		glm::vec2 closestPointOnBox = circlePosBox;
		glm::vec2 extents = box->getExtents();

		if (closestPointOnBox.x < -extents.x) closestPointOnBox.x = -extents.x;
		if (closestPointOnBox.x > extents.x) closestPointOnBox.x = extents.x;
		if (closestPointOnBox.y < -extents.y) closestPointOnBox.y = -extents.y;
		if (closestPointOnBox.y > extents.y) closestPointOnBox.y = extents.y;

		glm::vec2 closestPointOnBoxWorld = box->getPosition() + closestPointOnBox.x * box->getLocalX() + closestPointOnBox.y * box->getLocalY();
		glm::vec2 circleToBox = sphere->getPosition() - closestPointOnBoxWorld;
		float penetration = sphere->getRadius() - glm::length(circleToBox);

		if (penetration > 0)
		{
			glm::vec2 direction = glm::normalize(circleToBox);
			box->resolveCollision(sphere, closestPointOnBoxWorld, &direction, penetration);
			return true;
		}

		return false;
	}

	printf("sphere2Box collision function activated, but one or more are of the wrong type!\n");
	return false;
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
	Box* box1 = dynamic_cast<Box*>(actor1);
	Box* box2 = dynamic_cast<Box*>(actor2);

	if (box1 && box2)
	{
		glm::vec2 boxPos = box2->getPosition() - box1->getPosition();
		glm::vec2 normal(0, 0);
		glm::vec2 contact(0, 0);

		float penetration = 0;
		float numContacts = 0;
		box1->checkBoxCorners(*box2, contact, numContacts, penetration, normal);
		if (box2->checkBoxCorners(*box1, contact, numContacts, penetration, normal))
		{
			normal = -normal;
		}
		if (penetration > 0)
		{
			box1->resolveCollision(box2, contact / numContacts, &normal, penetration);
		}

		return true;
	}

	printf("box2Box collision function activated, but one or more are of the wrong type!\n");
	return false;
}

#pragma endregion