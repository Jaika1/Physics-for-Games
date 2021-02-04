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
	void ChangeScene(PhysicsScene* scene);
private:
	aie::Renderer2D* renderer = nullptr;
	aie::Font* font = nullptr;
	PhysicsScene* currentScene = nullptr;
};

extern PhysicsGame* gameInstance;