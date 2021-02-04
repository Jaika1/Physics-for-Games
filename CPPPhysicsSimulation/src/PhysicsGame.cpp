#include "PhysicsGame.h"
#include "PhysicsScene.h"
#include <Font.h>
#include <stdio.h>

using namespace aie;

PhysicsGame* gameInstance = nullptr;

PhysicsGame::~PhysicsGame() {
	delete renderer;
	delete font;
}

bool PhysicsGame::startup() {
	renderer = new Renderer2D();
	font = new aie::Font("./ext/fonts/consolas.ttf", 32);

	return true;
}

void PhysicsGame::shutdown() {

}

void PhysicsGame::update(float deltaTime) {
	//Update the current scene
	currentScene->Update(deltaTime);
}

void PhysicsGame::draw() {
	//Clear the screen
	clearScreen();

	renderer->begin();
	//Update the current scene
	currentScene->Draw();


	//Display current FPS
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	renderer->drawText(font, fps, 0, 720 - 32);

	renderer->end();
}

void PhysicsGame::ChangeScene(PhysicsScene* scene)
{
	if (currentScene) delete currentScene;
	currentScene = scene;
}
