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
	//Create the pointers to classes
	GenerationClass* terrainGenerator;
	WorldClass* world;
	//Create the menu
	MenuClass* mainMenu = new MenuClass(1);
	//Render the intro story
	mainMenu->RenderStory(-1);
	//Seed random to the current time
	srand(time(NULL));

	//While true since we call exit() to close
	while (true)
	{
		//Check if in menu
		while (mainMenu->MenuActive())
		{
			//Pass control to menu
			mainMenu->Tick();
		}
		//creat the world
		world = new WorldClass();
		//clear the screen then render a random players story
		mainMenu->ClearScreen();
		mainMenu->RenderStory(rand()%mainMenu->GetNumOfPlayers());
		//check if we are to load the world
		if (mainMenu->GetLoadWorld() == true)
			world->Load();
		else
		{
			//if new world, create the generator
			terrainGenerator = new GenerationClass();
			//generate and save the world
			terrainGenerator->Initialize(48, 32, mainMenu->GetSeed());
			world->Initialize(terrainGenerator->Generate(), 0, terrainGenerator->GetWidth(), terrainGenerator->GetHeight(), mainMenu->GetNumOfPlayers(), 0, mainMenu->GetNumAi());

			terrainGenerator->Save("Save/map", world->GetMap());
			world->Save();
			//free up our generator
			free(terrainGenerator);
		}
		//check if we are in game
		while (world->InGame())
		{
			//pass control to the world
			world->Tick();
		}
		//clear screen and play the winner's story
		mainMenu->ClearScreen();
		mainMenu->RenderStory(world->GetWinner() + 10);
		//free up our world
		free(world);
	}

	return 1;
}