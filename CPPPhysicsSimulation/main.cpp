#include "src/PhysicsGame.h"

int main()
{
	gameInstance = new PhysicsGame();
	gameInstance->run("Yet Another Physics Simulation", 1280, 720, false);
	delete gameInstance;

	return 0;
}