#include <iostream>
#include <Windows.h>
#include <ctime>

#include "worldclass.h"
#include "generationclass.h"

int main() 
{
	bool running = true;
	GenerationClass terrainGenerator;
	WorldClass world;
	terrainGenerator.Initialize(48, 32, 1337);
	CHAR_INFO * generation = terrainGenerator.Generate();
	world.Initialize(generation, 0, terrainGenerator.GetWidth(), terrainGenerator.GetHeight());

	terrainGenerator.Save("savedata.txt", world.GetMap());
	while (true)
	{
		world.Tick();
	}
	return 1;
}