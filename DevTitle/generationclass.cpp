#include "GenerationClass.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

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
	return 1;
}


CHAR_INFO * * GenerationClass::Generate()
{
	CHAR_INFO * * generating= (CHAR_INFO**)malloc(sizeof(CHAR_INFO*)*GenerationClass::height);
	for (int i = 0; i < GenerationClass::width; i++)
		generating[i] = (CHAR_INFO *)malloc(sizeof(CHAR_INFO)*GenerationClass::width);

	char rng;
	char prevrng = '1';
	int progress = 0;
	srand(GenerationClass::seed);
	for (int y = 0; y < GenerationClass::height; y++) 
	{
		for (int x = 0; x < GenerationClass::width; x++) 
		{
			rng = (rand() % 10);
			if (rand()%100 >= 80) 
			{
				generating[x][y].Char.AsciiChar = prevrng;
				prevrng = rng;
				progress++;
			}
			else 
			{
				generating[x][y].Char.AsciiChar = rng;
				progress++;
			}
		}
	}
	cout << "Generation Complete." << endl;
	return generating;
}

int GenerationClass::Save(char * filePath, CHAR_INFO * * saveData)
{
	ofstream savefile;
	savefile.open(filePath);
	for (int y = 0; y < GenerationClass::height; y++) {
		for (int x = 0; x < GenerationClass::width; x++) {
			savefile << saveData[x][y].Char.AsciiChar;
			savefile << saveData[x][y].Attributes;
		}
		savefile << endl;
	}
	savefile.flush();
	savefile.close();
	return 1;
}

/*
Possible terrain generation
0 - water
1 - plains
2 - hills
3 - forrest
4 - forrested hills
5 - mountain
*/