#pragma once
#include <glm.hpp>
#include <vector>

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* actor);
	void RemoveActor(PhysicsObject* actor);
	void Update(float deltaTime);
	void Draw();

	void SetGravity(const glm::vec2 grav) { gravity = grav; }
	glm::vec2 GetGravity() const { return gravity; }

	void SetTimeStep(const float tStep) { timeStep = tStep; }
	float GetTimeStep() const { return timeStep; }

protected:
	glm::vec2 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;
};