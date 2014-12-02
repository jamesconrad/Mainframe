#include <iostream>
#include <Windows.h>
#include <ctime>
#include <stdlib.h>

#define SCREEN_HEIGHT 51
#define SCREEN_WIDTH 83

#include "menuclass.h"
#include "worldclass.h"
#include "generationclass.h"

int main()
{
	GenerationClass* terrainGenerator;
	WorldClass* world;
	MenuClass* mainMenu = new MenuClass(1);

	mainMenu->RenderStory(-1);
	srand(time(NULL));
	while (true)
	{

		while (mainMenu->MenuActive())
		{
			mainMenu->Tick();
		}

		world = new WorldClass();

		mainMenu->ClearScreen();
		mainMenu->RenderStory(rand()%mainMenu->GetNumOfPlayers());

		if (mainMenu->GetLoadWorld() == true)
			world->Load();
		else
		{
			terrainGenerator = new GenerationClass();

			terrainGenerator->Initialize(48, 32, mainMenu->GetSeed());
			world->Initialize(terrainGenerator->Generate(), 0, terrainGenerator->GetWidth(), terrainGenerator->GetHeight(), mainMenu->GetNumOfPlayers(), 0, mainMenu->GetNumAi());

			terrainGenerator->Save("Save/map", world->GetMap());
			world->Save();

			free(terrainGenerator);
		}

		while (world->InGame())
		{
			world->Tick();
		}

		mainMenu->ClearScreen();
		mainMenu->RenderStory(world->GetWinner() + 10);
		free(world);
	}

	return 1;
}