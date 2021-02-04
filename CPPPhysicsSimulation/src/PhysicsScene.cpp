#include "PhysicsScene.h"
#include <glm.hpp>

PhysicsScene::PhysicsScene()
{
	SetGravity({0.0f, 0.0f});
	SetTimeStep(0.01f);
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

}

void PhysicsScene::RemoveActor(PhysicsObject* actor)
{

}

void PhysicsScene::Update(float deltaTime)
{

}

void PhysicsScene::Draw()
{

}
