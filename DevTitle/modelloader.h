#ifndef MODELLOADER_H
#define MODELLOADER_H
//ModelLoaderClass definition
#include <Windows.h>
#include <fstream>

class ModelLoaderClass
{
private:
	int width, height;
	CHAR_INFO* modelCharInfo;
	char* modelPath;
	FILE *saveFile;

public:
	ModelLoaderClass();
	ModelLoaderClass(const ModelLoaderClass&);
	~ModelLoaderClass();

	int Initialize();
	CHAR_INFO* GetModel(int modelNum, int x, int y);

};

#endif