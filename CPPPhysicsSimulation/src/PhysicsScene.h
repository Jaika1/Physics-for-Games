#pragma once
#include <glm.hpp>
#include <vector>

class PhysicsObject;

/// <summary>
/// A scene to be updated and rendered by PhysicsGame. Holds, updates and renders a collection of PhysicsObject instances.
/// </summary>
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	/// <summary>
	/// Adds the desired PhysicsObject to the scene.
	/// </summary>
	/// <param name="actor">The actor to add to the scene.</param>
	void addActor(PhysicsObject* actor);
	/// <summary>
	/// Removes the actor from the scene and calls delete on its pointer variable.
	/// </summary>
	/// <param name="actor">A pointer to an actor currently in the scene.</param>
	void removeActor(PhysicsObject* actor);
	/// <summary>
	/// Adds deltaTime to the currently passed time and moves through as many timesteps as is nessecary to update and check collisions for each actor in the scene.
	/// </summary>
	/// <param name="deltaTime">The anount of time passed since the last update was called.</param>
	void update(float deltaTime);
	/// <summary>
	/// Calls the draw function on every actor in the scene.
	/// </summary>
	void draw();

	/// <summary>
	/// Changes the gravity vector to the given value.
	/// </summary>
	/// <param name="gravity">The new gravity vector.</param>
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	/// <summary>
	/// Used to retrieve the current gravity vector. Modifying this value will not change the scenes gravity, use setGravity instead.
	/// </summary>
	/// <returns>The current gravity vector.</returns>
	glm::vec2 getGravity() const { return m_gravity; }

	/// <summary>
	/// Changes the fixed time-step for this scene, which is the amount of time in seconds to pass before updating each actor.
	/// </summary>
	/// <param name="gravity">The new time-step.</param>
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	/// <summary>
	/// Used to retrieve the current time-step value. Modifying this value will not change the scenes time-step, use setTimeStep instead.
	/// </summary>
	/// <returns>The current time-step value.</returns>
	float getTimeStep() const { return m_timeStep; }

protected:
	/// <summary>
	/// The current gravity vector.
	/// </summary>
	glm::vec2 m_gravity;
	/// <summary>
	/// The current fixed time-step.
	/// </summary>
	float m_timeStep;
	/// <summary>
	/// A list containing all actors that are managed by this scene instance.
	/// </summary>
	std::vector<PhysicsObject*> m_actors;
};