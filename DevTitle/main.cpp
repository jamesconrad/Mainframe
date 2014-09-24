#include <iostream>
#include <Windows.h>
#include <ctime>

#include "worldclass.h"
#include "generationclass.h"

int main() 
{
	time_t now = time(&now);
	time_t lastRender;
	bool running = true;
	GenerationClass terrainGenerator;
	WorldClass world;
	terrainGenerator.Initialize(48, 32, 50982);
	CHAR_INFO * generation = terrainGenerator.Generate();
	world.Initialize(generation, 0, terrainGenerator.GetWidth(), terrainGenerator.GetHeight());
	world.Render();
	
	time(&lastRender);

	terrainGenerator.Save("savedata.txt", world.GetMap());
	while (true)
	{
		world.Tick();
	}
	return 1;
}