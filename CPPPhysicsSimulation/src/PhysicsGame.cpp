#include "PhysicsGame.h"
#include "PhysicsScene.h"
#include <Font.h>
#include <stdio.h>
#include <Gizmos.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Sphere.h"
#include "Plane.h"
#include <Input.h>

using namespace aie;
using namespace glm;

PhysicsGame* GameInstance = nullptr;

PhysicsGame::~PhysicsGame() {
	delete m_renderer;
	delete m_font;
}

bool PhysicsGame::startup() {
	aie::Gizmos::create(255u, 255u, 65535u, 65535u);

	m_currentScene = new PhysicsScene();
	m_renderer = new Renderer2D();
	m_font = new aie::Font("./ext/fonts/consolas.ttf", 32);

	m_currentScene->addActor(new Sphere(vec2(0, 0), vec2(0, 0), 3.0f, 1.0f, vec4(1, 0, 0, 1)));
	m_currentScene->addActor(new Plane(vec2(0, 1), -50, vec4(0, 1, 0, 1)));
	m_currentScene->addActor(new Plane(vec2(0, -1), -50, vec4(0, 1, 0, 1)));
	m_currentScene->addActor(new Plane(vec2(1, 0), -90, vec4(0, 1, 0, 1)));
	m_currentScene->addActor(new Plane(vec2(-1, 0), -90, vec4(0, 1, 0, 1)));

	return true;
}

void PhysicsGame::shutdown() {

}

void PhysicsGame::update(float deltaTime) {
	aie::Gizmos::clear();

	//Update the current scene
	m_currentScene->update(deltaTime);
	m_currentScene->draw();
}

void PhysicsGame::draw() {
	//Clear the screen
	clearScreen();

	m_renderer->begin();

	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100/aspectRatio, 100/aspectRatio, -1.0f, 1.0f));

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
