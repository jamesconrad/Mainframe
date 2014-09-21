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
	
	world.Initialize(terrainGenerator.Generate(), 0, terrainGenerator.GetWidth(), terrainGenerator.GetHeight());
	world.Render();
	
	time(&lastRender);

	terrainGenerator.Save("savedata.txt", world.GetMap());
	
	while (running) 
	{
		//temp game loop
		world.Tick();

		/*
		//Checks to see if can move left, or right, and does so
		if (GetAsyncKeyState(VK_UP))
		{
			if (world.GetFrame() - terrainGenerator.GetWidth() > 0)
			{
				world.ChangeFrame(world.GetFrame() - terrainGenerator.GetWidth());
				Sleep(100);
			}
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (world.GetFrame() + terrainGenerator.GetWidth() < terrainGenerator.GetHeight() * terrainGenerator.GetWidth())
			{
				world.ChangeFrame(world.GetFrame() + terrainGenerator.GetWidth());
				Sleep(100);
			}
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (world.GetFrame() % terrainGenerator.GetWidth() != 0)
			{
				world.ChangeFrame(world.GetFrame() - 1);
				Sleep(100);
			}
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (world.GetFrame() % terrainGenerator.GetWidth() != terrainGenerator.GetWidth() - 1)
			{
				world.ChangeFrame(world.GetFrame() + 1);
				Sleep(100);
			}
		}

		time(&now);
		if (difftime(now, lastRender) >= 0.1)
		{
			world.Render();
			time(&lastRender);
		}


		if (GetAsyncKeyState(VK_ESCAPE))
			running = false;
		*/
	}
	return 1;
}