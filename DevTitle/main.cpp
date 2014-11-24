#include <iostream>
#include <Windows.h>
#include <ctime>

#define SCREEN_HEIGHT 51
#define SCREEN_WIDTH 83

#include "menuclass.h"
#include "worldclass.h"
#include "generationclass.h"

int main() 
{
//Prep the game
	GenerationClass* terrainGenerator;
	WorldClass* world;

//Setup the menu object
	MenuClass* mainMenu = new MenuClass(1);
	mainMenu->SetNumOptions(4);
	mainMenu->SetOptionText(0, "Singleplayer");
	mainMenu->SetOptionText(1, "Multiplayer");
	mainMenu->SetOptionText(2, "Help");
	mainMenu->SetOptionText(3, "Quit");

//Cycle menu to highlight first option
	mainMenu->OptionDown();
	mainMenu->OptionUp();

//Setup some input to the menu
	InputClass* menuInput = new InputClass();
	menuInput->Initialize();
	KEY_EVENT_RECORD input;

	int numOfPlayers = 6;

	while (mainMenu->MenuActive())
	{
		input = menuInput->GetKeypress();
		if (input.wVirtualKeyCode == VK_UP && input.bKeyDown == true)
			mainMenu->OptionUp();
		if (input.wVirtualKeyCode == VK_DOWN && input.bKeyDown == true)
			mainMenu->OptionDown();
		if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && mainMenu->GetId() == 1)
		{
			if (mainMenu->GetActiveOption() == 0)
			{
				mainMenu->ClearScreen();
				mainMenu->SetNumOptions(8);

				mainMenu->SetOptionText(0, "Seed:");
				mainMenu->SetOptionText(1, "seed"); // Possible change here
				mainMenu->SetOptionText(2, "Number of AI opponents");
				mainMenu->SetOptionText(3, "0");
				mainMenu->SetOptionText(4, "AI Handicap:");
				mainMenu->SetOptionText(5, "0"); //Possible change here
				mainMenu->SetOptionText(6, "Load Game"); //Possible change here
				mainMenu->SetOptionText(7, "Start Game");
				mainMenu->NewId(2);

				//Done. Now cycle selections
				mainMenu->OptionDown();
				mainMenu->OptionUp();
			}
			else if (mainMenu->GetActiveOption() == 1)
			{
				mainMenu->ClearScreen();
				mainMenu->SetNumOptions(6);

				mainMenu->SetOptionText(0, "Seed:");
				mainMenu->SetOptionText(1, "seed"); // Possible change here
				mainMenu->SetOptionText(2, "Number of Players");
				mainMenu->SetOptionText(3, "0");
				mainMenu->SetOptionText(4, " "); //Possible change here
				mainMenu->SetOptionText(5, "Start Game");
				mainMenu->NewId(2);

				//Done. Now cycle selections
				mainMenu->OptionDown();
				mainMenu->OptionUp();
			}
			else if (mainMenu->GetActiveOption() == 3)
				exit(1);
		}
		else if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && mainMenu->GetId() == 2)
		{
			if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && mainMenu->GetActiveOption() == 7)
			{
				//LETS PLAY -> Singleplayer
				int seed;
				srand(time(NULL));
				seed = rand()*rand();

				srand(seed);
				mainMenu->ClearScreen();

				terrainGenerator = new GenerationClass();
				world = new WorldClass();

				terrainGenerator->Initialize(48, 32, time(NULL));
				CHAR_INFO * generation = terrainGenerator->Generate();
				world->Initialize(generation, 0, terrainGenerator->GetWidth(), terrainGenerator->GetHeight(), numOfPlayers - 1, 0);

				terrainGenerator->Save("map", world->GetMap());
				world->Save();
				while (world->InGame())
				{
					world->Tick();
				}

			}
			else if (input.wVirtualKeyCode == VK_RETURN && input.bKeyDown == true && mainMenu->GetActiveOption() == 6)
			{
				if (FILE *file = fopen("misc", "r"))
				{
					fclose(file);
					world = new WorldClass();
					world->Load();
					while (world->InGame())
					{
						world->Tick();
					}
				}
				else
					mainMenu->SetOptionText(6, "No game data to load!");
			}
		}

		mainMenu->Render();
	}

	return 1;
}