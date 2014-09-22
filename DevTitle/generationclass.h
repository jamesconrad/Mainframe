#ifndef GENERATIONCLASS_H
#define GENERATIONCLASS_H

#include <Windows.h>

class GenerationClass 
{
public:
	GenerationClass();
	GenerationClass(const GenerationClass&);
	~GenerationClass();
	int Initialize(int, int, int);

	int GetWidth();
	int GetHeight();

	CHAR_INFO * Generate();
	int Save(char *, CHAR_INFO *);

private:
	char *generated;
	int seed;
	int width, height;
};

#endif