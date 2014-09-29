#include "generationclass.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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
	return 1;
}


CHAR_INFO * GenerationClass::Generate()
{
	//CHAR_INFO * * generating= (CHAR_INFO**)malloc(sizeof(CHAR_INFO*)*GenerationClass::height);
	//for (int i = 0; i < GenerationClass::width; i++)
	//	generating[i] = (CHAR_INFO *)malloc(sizeof(CHAR_INFO)*GenerationClass::width);
	CHAR_INFO *generating = (CHAR_INFO *)malloc(sizeof(CHAR_INFO)*width*height);
	char rng;
	char prevrng = '1';
	int progress = 0;
	srand(seed);
	for (int i = 0; i < width * height; i++) 
	{
		rng = (rand() % 10);
		if (rand()%100 >= 80) 
		{
			generating[i].Char.UnicodeChar = prevrng;
			prevrng = rng;
			progress++;
		}
		else 
		{
			generating[i].Char.UnicodeChar = rng;
			progress++;
		}
		generating[i].Attributes = 0x0001 | 0x0002 | 0x0004;
	}
	return generating;
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