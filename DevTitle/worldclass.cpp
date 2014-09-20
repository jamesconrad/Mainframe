/*
int initialize(vector<vector<char>>, int, int);
int changeFrame(int, int);
int updateTile(int, int, int);
int render();
*/
#include "WorldClass.h"
#include <iostream>
#include <Windows.h>

WorldClass::WorldClass()
{

}
WorldClass::WorldClass(const WorldClass&)
{

}

WorldClass::~WorldClass()
{

}

CHAR_INFO* WorldClass::GetMap()
{
	return WorldClass::worldMap;
}
int WorldClass::Initialize(CHAR_INFO* generation, int frame, int height, int width)
{
	WorldClass::class_ConBuffer.Initialize();
	WorldClass::worldMap = generation;
	WorldClass::frame = frame;
	WorldClass::height = height;
	WorldClass::width = width;

	WorldClass::cursor.Char.UnicodeChar = 43;
	WorldClass::cursor.Attributes = 0x0004 | 0x0008;
	return 1;
}

int WorldClass::UpdateTile(int x, int y, int newTile)
{
	WorldClass::worldMap[x].Char.AsciiChar = newTile;
	return 1;
}

int WorldClass::Render()
{
	class_ConBuffer.ClearConsole(class_ConBuffer.hConsole);
	WorldClass::class_ConBuffer.OutputScreen(WorldClass::worldMap, WorldClass::width, WorldClass::height, { 0 , 0 });
	
	
	
	SetConsoleCursorPosition(class_ConBuffer.hConsole, WorldClass::ConvertIndex(WorldClass::frame));

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

int WorldClass::GetFrame()
{
	return WorldClass::frame;
}

int WorldClass::ChangeFrame(int newFrame)
{
	WorldClass::frame = newFrame;
	return 1;
}

COORD WorldClass::ConvertIndex(int index)
{
	COORD indexCoord;
	indexCoord.Y = index / WorldClass::width;
	indexCoord.X = index % WorldClass::width;

	return indexCoord;
}

int WorldClass::ConvertCoord(COORD indexCoord)
{
	int index;
	index = indexCoord.Y * WorldClass::width;
	index += indexCoord.X;

	return index;
}