#include <iostream>
#include <Windows.h>
#include <ctime>

#include "worldclass.h"
#include "clientclass.h"
#include "serverclass.h"
#include "conbufferclass.h"
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
	terrainGenerator.Initialize(512, 512, 50982);
	
	world.Initialize(terrainGenerator.Generate(), 32, 32);
	world.Render(2, 2);
	
	time(&lastRender);

	terrainGenerator.Save("savedata.txt", world.GetMap());
	int worldFrameX = world.GetFrameX();
	int worldFrameY = world.GetFrameY();

	while (running) 
	{
		//temp game loop
		
		if (GetAsyncKeyState(VK_UP))
		{
			worldFrameY++;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			worldFrameY--;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			worldFrameX--;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			worldFrameX++;
			Sleep(100);
		}

		world.ChangeFrame(worldFrameX, worldFrameY);

		time(&now);
		if (difftime(now, lastRender) >= 0.5)
		{
			world.Render(2,2);
			time(&lastRender);
		}


		if (GetAsyncKeyState(VK_ESCAPE))
			running = false;
	}
	return 1;
}