#include "PhysicsScene.h"
#include <glm.hpp>
#include "PhysicsObject.h"

PhysicsScene::PhysicsScene() : m_gravity(glm::vec2(0.0f, 0.0f)), m_timeStep(0.01f)
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto a : m_actors) {
		delete a;
	}

	m_actors.clear();
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	auto a = std::find(m_actors.begin(), m_actors.end(), actor);
	m_actors.erase(a);
	delete* a;
}

void PhysicsScene::update(float deltaTime)
{
	static float timePassed = 0.0f;
	timePassed += deltaTime;

	while (timePassed >= m_timeStep)
	{
		for (auto a : m_actors)
		{
			a->fixedUpdate(m_gravity, m_timeStep);
		}

		timePassed -= m_timeStep;

		int actorCount = m_actors.size();

		for (int outer = 0; outer < actorCount - 1; outer++) {
			PhysicsObject* actor1 = m_actors[outer];

			for (int inner = outer + 1; inner < actorCount; inner++) {
				PhysicsObject* actor2 = m_actors[inner];

				if (PhysicsObject::checkCollision(actor1, actor2)) printf("Collision!\n");
			}
		}
	}
}

void PhysicsScene::draw()
{
	for (auto a : m_actors)
	{
		a->draw();
	}
}
