#include "PhysicsScene.h"
#include <glm.hpp>
#include "PhysicsObject.h"

PhysicsScene::PhysicsScene() : gravity({ 0.0f, 0.0f }), timeStep(0.01f)
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto a : actors) {
		delete a;
	}

	actors.clear();
}

void PhysicsScene::AddActor(PhysicsObject* actor)
{
	actors.push_back(actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* actor)
{
	auto a = std::find(actors.begin(), actors.end(), actor);
	actors.erase(a);
	delete* a;
}

void PhysicsScene::Update(float deltaTime)
{
	static float timePassed = 0.0f;
	timePassed += deltaTime;

	while (timePassed >= timeStep)
	{
		for (auto a : actors)
		{
			a->FixedUpdate(gravity, timeStep);
		}

		timePassed -= timeStep;
	}
}

void PhysicsScene::Draw()
{
	for (auto a : actors)
	{
		a->Draw();
	}
}
