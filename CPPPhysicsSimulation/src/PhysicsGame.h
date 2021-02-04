#pragma once
#include <Application.h>
#include <Renderer2D.h>

class PhysicsScene;

class PhysicsGame :
	public aie::Application
{
public:
	~PhysicsGame();
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();
	void changeScene(PhysicsScene* scene);
private:
	aie::Renderer2D* m_renderer = nullptr;
	aie::Font* m_font = nullptr;
	PhysicsScene* m_currentScene = nullptr;
};

extern PhysicsGame* GameInstance;