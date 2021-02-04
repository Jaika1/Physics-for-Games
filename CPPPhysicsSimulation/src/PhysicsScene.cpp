#include "PhysicsScene.h"
#include <glm.hpp>

PhysicsScene::PhysicsScene()
{
	SetGravity({0.0f, 0.0f});
	SetTimeStep(0.01f);
}
