#include "src/PhysicsGame.h"

int main()
{
	GameInstance = new PhysicsGame();
	GameInstance->run("Yet Another Physics Simulation", 1280, 720, false);
	delete GameInstance;

	return 0;
}