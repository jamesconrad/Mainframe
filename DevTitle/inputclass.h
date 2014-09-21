#ifndef INPUTCLASS_H
#define INPUTCLASS_H

#include <Windows.h>

class InputClass {
private:
	HANDLE hConsole;
	DWORD nLength;
	DWORD * eventsRead;
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	int Initialize();
	KEY_EVENT_RECORD GetKeypress();
};

#endif