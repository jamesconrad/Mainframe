#include "modelloader.h"
#include <fstream>
#include <iostream>

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
	char* memoryBuffer = (char*)malloc(sizeof(CHAR_INFO)*width*height);

	std::ifstream load("model", std::ios::binary);

	load >> memoryBuffer;
	memcpy(modelCharInfo, memoryBuffer, sizeof(CHAR_INFO)*width*height);

	free(memoryBuffer);

	return modelCharInfo;
}