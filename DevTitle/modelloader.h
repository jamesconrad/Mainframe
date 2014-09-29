#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <Windows.h>
#include <iostream>
#include <fstream>

class ModelLoaderClass
{
private:
	std::ifstream modelFile;
	int width, height;
	CHAR_INFO* modelCharInfo;

public:
	ModelLoaderClass();
	ModelLoaderClass(const ModelLoaderClass&);
	~ModelLoaderClass();

	int Initialize();
	CHAR_INFO* GetModel(int modelNum);

};

#endif