#pragma once
#include <Application.h>
#include <Renderer2D.h>

class PhysicsScene;

/// <summary>
/// The class that manages the application window and game loop, along with scene selection and switching.
/// </summary>
class PhysicsGame :
	public aie::Application
{
public:
	~PhysicsGame();
	/// <summary>
	/// Overridden from aie::Aplication, called right after the window is initialised.
	/// </summary>
	/// <returns>Wether the startup succeeded or not.</returns>
	virtual bool startup();
	/// <summary>
	/// Overridden from aie::Aplication, called when the window is closing. Currently empty.
	/// </summary>
	virtual void shutdown();
	/// <summary>
	/// Overridden from aie::Application. Called each frame, executes the update method in the current scene.
	/// </summary>
	/// <param name="deltaTime">The amount of time that has elapsed since the last update.</param>
	virtual void update(float deltaTime);
	/// <summary>
	/// Overridden from aie::Application. Called each frame, clears the screen and calls aie::Gizmos::draw2D. Also displays the current FPS in the top right corner.
	/// </summary>
	virtual void draw();
	/// <summary>
	/// Deletes the current scene (if any is loaded) and sets the scene to the new one specified.
	/// </summary>
	/// <param name="scene">A pointer to the new scene to switch to.</param>
	void changeScene(PhysicsScene* scene);
	/// <summary>
	/// Returns the current scene (if any is loaded).
	/// </summary>
	/// <param name="scene">The current scene being used by the game.</param>
	const PhysicsScene getScene();
private:
	/// <summary>
	/// A pointer to the renderer used to display stuff on-screen.
	/// </summary>
	aie::Renderer2D* m_renderer = nullptr;
	/// <summary>
	/// The font used when drawing the FPS counter.
	/// </summary>
	aie::Font* m_font = nullptr;
	/// <summary>
	/// The currently active scene.
	/// </summary>
	PhysicsScene* m_currentScene = nullptr;
};

/// <summary>
/// A global instance of PhysicsGame for easy reference.
/// </summary>
extern PhysicsGame* GameInstance;