#include "PhysicsGame.h"
#include "PhysicsScene.h"
#include <Font.h>
#include <stdio.h>
#include <Gizmos.h>

using namespace aie;

PhysicsGame* GameInstance = nullptr;

PhysicsGame::~PhysicsGame() {
	delete m_renderer;
	delete m_font;
}

bool PhysicsGame::startup() {
	aie::Gizmos::create(255u, 255u, 65535u, 65535u);

	changeScene(new PhysicsScene());
	m_renderer = new Renderer2D();
	m_font = new aie::Font("./ext/fonts/consolas.ttf", 32);

	return true;
}

void PhysicsGame::shutdown() {

}

void PhysicsGame::update(float deltaTime) {
	//Update the current scene
	m_currentScene->update(deltaTime);
}

void PhysicsGame::draw() {
	//Clear the screen
	clearScreen();

	m_renderer->begin();
	//Update the current scene
	m_currentScene->draw();


	//Display current FPS
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_renderer->drawText(m_font, fps, 0, 720 - 32);

	m_renderer->end();
}

void PhysicsGame::changeScene(PhysicsScene* scene)
{
	if (m_currentScene) delete m_currentScene;
	m_currentScene = scene;
}
