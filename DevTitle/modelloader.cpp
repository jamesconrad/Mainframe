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
	width = 8;
	height = 8;

	modelCharInfo = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*width*height);

	modelFile.open("models.txt", std::ios::in | std::ios::binary);

	return 1;
}

CHAR_INFO* ModelLoaderClass::GetModel(int modelNum)
{
	for (int i = 0; i < width*height; ++i)
	{
	}

	return modelCharInfo;
}