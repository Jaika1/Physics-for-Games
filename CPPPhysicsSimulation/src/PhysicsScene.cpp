#include "PhysicsScene.h"
#include <glm.hpp>
#include "PhysicsObject.h"
#include "RigidBody.h"
#include <Input.h>
#include "Sphere.h"

PhysicsScene::PhysicsScene() : m_gravity(glm::vec2(0.0f, 0.0f)), m_timeStep(0.01f)
{
	// The initializer code above merely sets the gravity vector to 0, and the fixed time step to 0.01f.
}

PhysicsScene::~PhysicsScene()
{
	// Safely iterates through our list of actors and deletes them one-by-one.
	for (auto a : m_actors) {
		if (a) delete a;
	}

	// Clears the list of actors. This is possibly a redundant call.
	m_actors.clear();
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	// Simply add the actor to the back of out list. No other action here is required.
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	// Find the actor being referenced.
	auto a = std::find(m_actors.begin(), m_actors.end(), actor);

	// Check to see if an actor was actually found in the list, then safely remove and delete it.
	if (a != m_actors.end()) {
		m_actors.erase(a);
		if (*a) delete *a;
	}
}

void PhysicsScene::update(float deltaTime)
{
	// A static variable that will count up constantly each update, which will be used to keep track of when
	// the amount of time storred as m_timeStep as passed.
	static float timePassed = 0.0f;
	// Add deltaTime to our static variable.
	timePassed += deltaTime;

	if (aie::Input::getInstance()->wasKeyPressed(aie::INPUT_KEY_SPACE)) {
		Sphere* s2 = new Sphere(glm::vec2(7, 0), glm::vec2(rand() / (RAND_MAX / 8.0f), rand() / (RAND_MAX / 8.0f)), 1, 3, glm::vec4(1, 1, 1, 1));
		addActor(s2);
	}

	// Keep updating our actors until timePassed is less than m_timeStep.
	for (; timePassed >= m_timeStep; timePassed -= m_timeStep)
	{
		// Update each actor in the scene.
		for (auto a : m_actors)
		{
			a->fixedUpdate(m_gravity, m_timeStep);
		}

		// Check collisions between all actors while making as few checks as possible. Good enough for what we're doing.
		int actorCount = m_actors.size();

		for (int outer = 0; outer < actorCount - 1; outer++) {
			PhysicsObject* actor1 = m_actors[outer];

			for (int inner = outer + 1; inner < actorCount; inner++) {
				PhysicsObject* actor2 = m_actors[inner];

				PhysicsObject::checkCollision(actor1, actor2);
			}
		}
	}
}

void PhysicsScene::draw()
{
	// Simply iterate through each actor in the list and call its draw function.
	for (auto a : m_actors)
	{
		a->draw();
	}
}

void PhysicsScene::ApplyContactForces(Rigidbody* body1, Rigidbody* body2, glm::vec2 norm, float pen)
{
	float body2Mass = body2 ? body2->getMass() : INT_MAX;
	float body1Factor = body2Mass / (body1->getMass() + body2Mass);

	body1->setPosition(body1->getPosition() - body1Factor * norm * pen);
	if (body2) body2->setPosition(body2->getPosition() + (1 - body1Factor) * norm * pen);
}
