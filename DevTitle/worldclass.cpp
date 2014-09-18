/*
int initialize(vector<vector<char>>, int, int);
int changeFrame(int, int);
int updateTile(int, int, int);
int render();
*/
#include <vector>
#include "worldclass.h"
#include <iostream>
using namespace std;

worldclass::worldclass()
{

}
worldclass::worldclass(const worldclass&)
{

}

worldclass::~worldclass()
{

}

vector<vector<char>> worldclass::getMap()
{
	return worldclass::worldmap;
}
int worldclass::initialize(vector<vector<char>> generation, int framex, int framey)
{
	worldclass::worldmap = generation;
	worldclass::framex = framex;
	worldclass::framey = framey;
	return 1;
}

int worldclass::updateTile(int x, int y, int newTile)
{
	worldclass::worldmap[x][y] = newTile;
	return 1;
}

int worldclass::render(int rendersizeX, int rendersizeY)
{
	//Note colouring system still needs to be impletmented
	//Switch cases would be best ex. case ASCIIChar-PlayerNum > 0; setcolour(playercolour); break;
	cout << "Ready to render world." << endl;
	for (int y = (worldclass::framey - rendersizeY); y <= (worldclass::framey + rendersizeY); y++){
		if (y >= 0) {
			for (int x = (worldclass::framex - rendersizeX); x <= (worldclass::framex + rendersizeX); x++){
				if (x >= 0){
					if (y == worldclass::framey && x == worldclass::framex && worldclass::cursorRenderd == false){
						worldclass::cursorRenderd = true;
						cout << "+";
					}
					else{
						cout << worldclass::worldmap[x][y];
						worldclass::cursorRenderd = false;
					}
				}
			}
			cout << endl;
		}
	}
	return 1;
}

int worldclass::getFrameX()
{
	return worldclass::framex;
}

int worldclass::getFrameY()
{
	return worldclass::framey;
}

int worldclass::changeFrame(int newX, int newY)
{
	worldclass::framex = newX;
	worldclass::framey = newY;
	return 1;
}