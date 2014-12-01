#include "modelloader.h"
#include <fstream>

ModelLoaderClass::ModelLoaderClass()
{
}

ModelLoaderClass::ModelLoaderClass(const ModelLoaderClass&)
{
}

ModelLoaderClass::~ModelLoaderClass()
{
}

int ModelLoaderClass::Initialize()
{
	width = 29;
	height = 32;

	modelCharInfo = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*width*height);
	modelPath = new char[32];

	return 1;
}

CHAR_INFO* ModelLoaderClass::GetModel(int modelNum, int x, int y)
{
	SMALL_RECT renderRect;
	renderRect.Left = x;
	renderRect.Top = y;
	renderRect.Right = x + 29;
	renderRect.Bottom = y + 32;

	COORD len = { 29, 24 };

	switch (modelNum)
	{
	case -1:
		modelPath = "Models/title";
		renderRect.Right = x + 67;
		renderRect.Bottom = y + 9;
		len.X = 67;
		len.Y = 9;
		break;
	case 0:
		modelPath = "Models/HQ";
		break;
	case 1:
		modelPath = "Models/builder";
		break;
	case 2:
		modelPath = "Models/soldier";
		break;
	case 3:
		modelPath = "Models/tower";
		break;
	case 4:
		modelPath = "Models/wall";
		break;
	}
	saveFile = fopen(modelPath, "rb");
	fread(modelCharInfo, sizeof(CHAR_INFO), width*height, saveFile);

	fclose(saveFile);


	WriteConsoleOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), modelCharInfo, len, { 0, 0 }, &renderRect);
	
	return modelCharInfo;
}