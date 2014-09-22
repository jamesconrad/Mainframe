#include <iostream>
#include <Windows.h>
#include <ctime>

#include "worldclass.h"
#include "clientclass.h"
#include "serverclass.h"
#include "generationclass.h"

/*
enum TextColour
{
	tWhite = (0x001 | 0x002 | 0x004),
	tRed = (0x004),
	tBlue = (0x001),
	tGreen = (0x002)
};
enum BackgroundColour
{
	bWhie = (0x010 | 0x020 | 0x030),
	bRed = (0x040),
	bBlue = (0x010),
	bGreen = (0x020)
};
*/

/*
TODO:
http://msdn.microsoft.com/en-us/library/ms682073(v=vs.85).aspx

*/

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