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
#include <time.h>
#include "Box.h"

using namespace aie;
using namespace glm;
 
PhysicsGame* GameInstance = nullptr;

PhysicsGame::~PhysicsGame() {
	// Safely frees up memory for each pointer this instance owns.
	if (m_renderer) delete m_renderer;
	if (m_font) delete m_font;
	if (m_currentScene) delete m_currentScene;
}

bool PhysicsGame::startup() {
	// Sets the number of 2D lines and tris that we can draw to a relatively high value so we can draw many objects.
	aie::Gizmos::create(255u, 255u, 65535u, 65535u);

	// Initializes instances of a new scene, 2D renderer and font.
	m_currentScene = new PhysicsScene();
	m_renderer = new Renderer2D();
	m_font = new aie::Font("./ext/fonts/consolas.ttf", 32);

	srand(time(nullptr));

	// Adding a bunch of spheres to the scene for testing purposes. 
	for (int i = 0; i < 20; ++i) {
		Sphere* s = new Sphere(
			vec2((rand() / (RAND_MAX / 170.0f)) - 85.0f, (rand() / (RAND_MAX / 90.0f)) - 45.0f),
			vec2((rand() / (RAND_MAX / 20.0f)) - 10.0f, (rand() / (RAND_MAX / 20.0f)) - 10.0f),
			(rand() / (RAND_MAX / 2.0f)) + 1.0f,
			(rand() / (RAND_MAX / 4.0f)) + 1.0f,
			vec4(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1));
		s->setKinematic(rand() % 2);
		m_currentScene->addActor(s);
	}

	// Adding a bunch of boxes to the scene for testing purposes. 
	for (int i = 0; i < 20; ++i) {
		Box* b = new Box(
			vec2((rand() / (RAND_MAX / 170.0f)) - 85.0f, (rand() / (RAND_MAX / 90.0f)) - 45.0f),
			vec2((rand() / (RAND_MAX / 20.0f)) - 10.0f, (rand() / (RAND_MAX / 20.0f)) - 10.0f),
			(rand() / (RAND_MAX / 2.0f)) + 1.0f,
			(rand() / (RAND_MAX / 2.0f)) + 1.0f,
			vec2((rand() / (RAND_MAX / 10.0f)) + 1.0f, (rand() / (RAND_MAX / 10.0f)) + 1.0f),
			vec4(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1));
		b->setKinematic(rand() % 2);
		m_currentScene->addActor(b);
	}

	m_currentScene->addActor(new Plane(vec2(0, 1), -53, vec4(0, 1, 0, 1)));
	m_currentScene->addActor(new Plane(vec2(0, -1), -53, vec4(0, 1, 0, 1)));
	m_currentScene->addActor(new Plane(vec2(1, 0), -97, vec4(0, 1, 0, 1)));
	m_currentScene->addActor(new Plane(vec2(-1, 0), -97, vec4(0, 1, 0, 1)));

	m_currentScene->setGravity({ 0, -9.1f });

	// Return true for a successful startup.
	return true;
}

void PhysicsGame::shutdown() {
	// Unused.
}

void PhysicsGame::update(float deltaTime) {
	// Clears each object to render from the queue, as we are beginning a new update.
	aie::Gizmos::clear();

	//Update the current scene and call draw to add each actor to the render queue in Gizmos.
	m_currentScene->update(deltaTime);
	m_currentScene->draw();
}

void PhysicsGame::draw() {
	// Clear the screen ready for a new draw.
	clearScreen();

	m_renderer->begin();

	// Draw everything held in aie::Gizmos.
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100/aspectRatio, 100/aspectRatio, -1.0f, 1.0f));

	// Display the current FPS. An array size of 15 is used here since the fixed chars here will always use 5 chars,
	// and the maximum written length of a uint is 10 chars, even though such a feat would be legendary.
	char fps[15];
	sprintf_s(fps, 15, "FPS: %i", getFPS());
	m_renderer->drawText(m_font, fps, 0, 720 - 32);

	m_renderer->end();
}

void PhysicsGame::changeScene(PhysicsScene* scene)
{
	// Safely deletes the reference to the current scene if it exists.
	if (m_currentScene) delete m_currentScene;

	// Set the current scene to the newly inserted one.
	m_currentScene = scene;
}

PhysicsScene* PhysicsGame::getScene() const
{
	return m_currentScene;
}
