#pragma once
#include <glm.hpp>

// Foward decleration here is nessecary for the typedef below.
class PhysicsObject;

/// <summary>
/// A type definition to point to a function that takes 2 PhysicsObject pointers, used to check and resolve collisions.
/// </summary>
typedef bool (*collisionCheck_t)(PhysicsObject* actor1, PhysicsObject* actor2);

/// <summary>
/// Contains entries for each shape type, to be used as IDs for discerning each one. Also has an entry for retreiving how many different shape types there are.
/// </summary>
enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX,
	COLLISIONROWSIZE
};

/// <summary>
/// Represents the most basic form of an object that can be placed in the world. Designed to be inherited by other types, creating an instance of this on its own is heavily advised against. Also contains functions used for collision detection between different object types.
/// </summary>
class PhysicsObject
{
protected:
	/// <summary>
	/// Used to initialized this object and assign it an ID, which will be used for identifying it by other functions.
	/// </summary>
	/// <param name="shapeID">What type of shape this instance is.</param>
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID), m_elasticity(0.7f) {}
	/// <summary>
	/// Represents the type of shape this is. Can only be set by the initializer.
	/// </summary>
	const ShapeType m_shapeID;
	/// <summary>
	/// The elasticity of this object. In short terms, this represents the efficiency how much kinetic energy is maintained after a collision 
	/// </summary>
	float m_elasticity;

public:
	/// <summary>
	/// Physics update, called when each fixed time-step has elapsed as defined in PhysicsScene. Must be overridden.
	/// </summary>
	/// <param name="gravity">The gravity vector.</param>
	/// <param name="timeStep">The length of a time-step.</param>
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	/// <summary>
	/// Queues the object in question for drawing. Must be overriden.
	/// </summary>
	virtual void draw() = 0;
	/// <summary>
	/// Currently unused, does absolutely nothing.
	/// </summary>
	virtual void resetPosition() {};
	/// <summary>
	/// Used to check and handle a potential collision between 2 different objects.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool checkCollision(PhysicsObject* actor1, PhysicsObject* actor2);

	/// <summary>
	/// Used to retrieve this objects elasticity. Modifying this value will not change the elasticity for this object.
	/// </summary>
	/// <returns>This objects elasticity.</returns>
	float getElasticity() const { return m_elasticity; }
private:
	/// <summary>
	/// An array of function pointers that is used to determine the function required for collision checks between 2 PhysicsObject instances.
	/// </summary>
	static collisionCheck_t collisionCheckFunctionArray[];

	#pragma region Collision Check Functions
	/// <summary>
	/// This function will always return false since planes are always static. This function exists because the pointer array we use requires it.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor.</param>
	/// <param name="actor2">A pointer to the second actor.</param>
	/// <returns>Will always return false.</returns>
	static bool plane2Plane(PhysicsObject* actor1, PhysicsObject* actor2);
	/// <summary>
	/// Attempts to cast actor 1 to a plane and actor 2 to a sphere, then checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool plane2Sphere(PhysicsObject* actor1, PhysicsObject* actor2);
	/// <summary>
	/// Attempts to cast actor 1 to a plane and actor 2 to a box, then checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool plane2Box(PhysicsObject* actor1, PhysicsObject* actor2);

	/// <summary>
	/// Attempts to cast actor 1 to a sphere and actor 2 to a plane, then checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool sphere2Plane(PhysicsObject* actor1, PhysicsObject* actor2);
	/// <summary>
	/// Attempts to cast both actors to spheres and checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool sphere2Sphere(PhysicsObject* actor1, PhysicsObject* actor2);
	/// <summary>
	/// Attempts to cast actor 1 to a sphere and actor 2 to a box, then checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool sphere2Box(PhysicsObject* actor1, PhysicsObject* actor2);

	/// <summary>
	/// Attempts to cast actor 1 to a box and actor 2 to a plane, then checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool box2Plane(PhysicsObject* actor1, PhysicsObject* actor2);
	/// <summary>
	/// Attempts to cast actor 1 to a box and actor 2 to a sphere, then checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool box2Sphere(PhysicsObject* actor1, PhysicsObject* actor2);
	/// <summary>
	/// Attempts to cast both actors to boxes and checks for a collision between them.
	/// </summary>
	/// <param name="actor1">A pointer to the first actor to test against actor2 for a collision.</param>
	/// <param name="actor2">A pointer to the second actor to test against actor1 for a collision.</param>
	/// <returns>True if a collision has occured, otherwise false.</returns>
	static bool box2Box(PhysicsObject* actor1, PhysicsObject* actor2);
	#pragma endregion
};