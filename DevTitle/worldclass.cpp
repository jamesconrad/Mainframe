/*
int initialize(vector<vector<char>>, int, int);
int changeFrame(int, int);
int updateTile(int, int, int);
int render();
*/
#include "WorldClass.h"
#include <iostream>
#include <Windows.h>
using namespace std;

WorldClass::WorldClass()
{

}
WorldClass::WorldClass(const WorldClass&)
{

}

WorldClass::~WorldClass()
{

}

CHAR_INFO** WorldClass::GetMap()
{
	return WorldClass::worldMap;
}
int WorldClass::Initialize(CHAR_INFO** generation, int framex, int framey)
{
	WorldClass::class_ConBuffer.Initialize();
	WorldClass::worldMap = generation;
	WorldClass::framex = framex;
	WorldClass::framey = framey;
	return 1;
}

int WorldClass::UpdateTile(int x, int y, int newTile)
{
	WorldClass::worldMap[x][y].Char.AsciiChar = newTile;
	return 1;
}

int WorldClass::Render(int rendersizeX, int rendersizeY)
{

	for (int y = WorldClass::framey - rendersizeY; y <= WorldClass::framey + rendersizeY; y++)
	{
		if (y >= 0)
		{
			WorldClass::class_ConBuffer.OutputScreen(WorldClass::worldMap[y], rendersizeX * 2, { 0, y });
		}
	}
	WorldClass::class_ConBuffer.SwapBuffer();

	//COMPLETE REWORK, LEGACY CODE BELOW
	//Note colouring system still needs to be impletmented
	//Switch cases would be best ex. case ASCIIChar-PlayerNum > 0; setcolour(playercolour); break;
	/*
	cout << "Ready to render world." << endl;
	for (int y = (WorldClass::framey - rendersizeY); y <= (WorldClass::framey + rendersizeY); y++){
		if (y >= 0) {
			for (int x = (WorldClass::framex - rendersizeX); x <= (WorldClass::framex + rendersizeX); x++){
				if (x >= 0){
					if (y == WorldClass::framey && x == WorldClass::framex && WorldClass::cursorRenderd == false){
						WorldClass::cursorRenderd = true;
						cout << "+";
					}
					else{
						WorldClass::worldmap[x][y];
						WorldClass::cursorRenderd = false;
					}
				}
			}
			cout << endl;
		}
	}
	*/

	return 1;
}

int WorldClass::GetFrameX()
{
	return WorldClass::framex;
}

int WorldClass::GetFrameY()
{
	return WorldClass::framey;
}

int WorldClass::ChangeFrame(int newX, int newY)
{
	WorldClass::framex = newX;
	WorldClass::framey = newY;
	return 1;
}