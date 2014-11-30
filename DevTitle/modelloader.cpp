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

	return 1;
}

CHAR_INFO* ModelLoaderClass::GetModel(int modelNum)
{
	FILE *saveFile;
	char* modelPath = new char[32];
	switch (modelNum)
	{
	case 0:
		modelPath = "Models/HQ";
	case 1:
		modelPath = "Models/builder";
		break;
	case 2:
		modelPath = "Models/soldier";
		break;
	}
	saveFile = fopen(modelPath, "rb");
	fread(modelCharInfo, sizeof(CHAR_INFO), width*height, saveFile);
	
	delete[] modelPath;
	fclose(saveFile);

	SMALL_RECT renderRect;
	renderRect.Left = 51;
	renderRect.Top = 3;
	renderRect.Right = 51 + 29;
	renderRect.Bottom = 3 + 32;

	WriteConsoleOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), modelCharInfo, { 32, 24 }, { 0, 0 }, &renderRect);
	
	return modelCharInfo;
}