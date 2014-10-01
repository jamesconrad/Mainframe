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
	terrainGenerator.Initialize(48, 32, time(NULL));
	CHAR_INFO * generation = terrainGenerator.Generate();
	world.Initialize(generation, 0, terrainGenerator.GetWidth(), terrainGenerator.GetHeight());

	terrainGenerator.Save("map", world.GetMap());
	while (true)
	{
		world.Tick();
	}
	return 1;
}