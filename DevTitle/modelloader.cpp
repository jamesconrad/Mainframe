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
	saveFile = fopen("Models/builder", "rb");
	fread(modelCharInfo, sizeof(CHAR_INFO), width*height, saveFile);

	return modelCharInfo;
}