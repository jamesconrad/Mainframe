#include "generationclass.h"
#include <fstream>

GenerationClass::GenerationClass()
{
}

GenerationClass::GenerationClass(const GenerationClass& other)
{
}

GenerationClass::~GenerationClass()
{
}

int GenerationClass::Initialize(int width, int height, int seed) {
	GenerationClass::width = width;
	GenerationClass::height = height;
	GenerationClass::seed = seed;

	water.Char.UnicodeChar = 126;
	water.Attributes = 0x0001;

	road.Char.UnicodeChar = 9618;
	road.Attributes = 0x0007;

	land.Char.UnicodeChar = 9617;
	land.Attributes = 0x0002;

	//water, road, land, structure
	return 1;
}

CHAR_INFO* GenerationClass::Generate()
{
	lT_count = width * height * 0.600;
	rT_count = lT_count * 0.300;
	tT_count = lT_count * 0.150;
	eT_count = lT_count * 0.050;

	tile_ratio = 0.900;

	map = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* width * height);
	for (int i = 0; i < width * height; i++) map[i] = water;


	srand(seed);

	/*
	BEGIN GEN
	*/

	//Beginning tile
	tile_start = width / 2 + width * (height / 2 - 1);

	MainGen(tile_start);
	RoadGen(tile_start, 0);

	/*
	TerrainGen(firstTile);
	ResourceGen(firstTile);
	*/

	return map;
}

/*
HELPER FUNCTIONS
*/
void GenerationClass::MainGen(int tile_at)
{
	//returns if it can't place anymore blocks up
	if (lT_count <= 0)
		return;


	//generate tiles to the left (-1) or right (1)
	int side = (tile_at % width < width / 2) ? -1 : 1;

	//generates a tile on the current index
	map[tile_at] = land;
	lT_count--;

	//generate all tiles to the side of current
	for (int i = -1; i < tile_ratio * (width / 2); i++)
	{
		map[tile_at + side * i] = land;
		lT_count--;
	}

	//decrease how far tiles can be generated after a single row has been done
	tile_ratio *= pow(tile_ratio, 0.05);

	//where to generate next
	if (side == 1)
	if (tile_at / width < height / 2)		//if on top
		MainGen(tile_at - 1);
	else
		MainGen(height * width - tile_at - width);
	else
	if (tile_at / width < height / 2)		//if on top
		MainGen(height * width - tile_at - 2);
	else
		MainGen(tile_at + 1);

	return;
}

void GenerationClass::RoadGen(int tile_at, short dir)
{
	//returns if it can't place anymore blocks up
	if (rT_count <= 0)
		return;

	map[tile_at] = road;
	rT_count--;

	int tile_next;
	short dir_next = dir;

	//random chance to change directions
	if ((double)rand() / RAND_MAX <= 1 / avg_r_len)
	if ((double)rand() / RAND_MAX <= 0.5)
		dir_next = abs((dir - 1) % 4);
	else
		dir_next = (dir + 1) % 4;

	switch (dir_next)
	{
	case 0:
		tile_next = tile_at - width;
		break;
	case 1:
		tile_next = tile_at + 1;
		break;
	case 2:
		tile_next = tile_at + width;
		break;
	case 3:
		tile_next = tile_at - 1;
		break;
	}

	if (map[tile_next].Char.UnicodeChar == water.Char.UnicodeChar)
	{
		tile_next = tile_start;
		dir_next = (double)rand() / RAND_MAX * 4;
	}

	RoadGen(tile_next, dir_next);
}

bool GenerationClass::NotAtBorder(int tile)
{
	if (tile < width)
		return false;
	if (tile > width * (height - 1))
		return false;
	if (tile % width == 0 || tile % width == width - 1)
		return false;

	return true;
}

bool GenerationClass::IsLand(int tile)
{
	if (map[tile].Char.UnicodeChar == land.Char.UnicodeChar)
		return true;
	else
		return false;
}

int GenerationClass::Save(char* filePath, CHAR_INFO* saveData)
{
	FILE *saveFile;
	saveFile = fopen("map", "wb");
	fwrite(saveData, sizeof(CHAR_INFO), width*height, saveFile);
	return 1;
}


int GenerationClass::GetWidth() 
{
	return width;
}

int GenerationClass::GetHeight()
{
	return height;
}