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

//Used to easily fill CHAR_INFO arrays
void ConvertString(const char * text, CHAR_INFO * result, int hexAttribute)
{
	wchar_t* converted = new wchar_t[strlen(text)];
	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, strlen(text) * sizeof(char), converted, strlen(text));
	for (int i = 0; i < strlen(text); i++)
	{
		result[i].Char.UnicodeChar = text[i];
		result[i].Attributes = hexAttribute;
	}
	delete[]converted;
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
	//find out which model to load
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
		modelPath = "Models/firewall";
		break;
	}
	saveFile = fopen(modelPath, "rb");
	if (saveFile != nullptr)
	{
		fread(modelCharInfo, sizeof(CHAR_INFO), width*height, saveFile);
		fclose(saveFile);
	}
	else
	{
		char* errorstring = (char*)malloc(sizeof(char)*width*height);
		memset(errorstring, ' ', width*height);
		memcpy(errorstring, "Error model file not found: ", 28);
		memcpy(errorstring + 28, modelPath, strlen(modelPath));
		errorstring[width*height - 1] = '\0';
		ConvertString(errorstring, modelCharInfo, 0x0001 | 0x0002 | 0x0004 | 0x0008 | 0x0040 | 0x0080);
	}
	//render the model to the given position, starting at the top left corner
	WriteConsoleOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), modelCharInfo, len, { 0, 0 }, &renderRect);
	
	return modelCharInfo;
}