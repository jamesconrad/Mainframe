#include "inputclass.h"

InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass&)
{
}

InputClass::~InputClass()
{
}

int InputClass::Initialize()
{
	hConsole = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);
	nLength = 1;
	return 1;
}

KEY_EVENT_RECORD InputClass::GetKeypress()
{
	INPUT_RECORD inputRecord;
	DWORD eventsRead;
	ReadConsoleInput(InputClass::hConsole, &inputRecord, InputClass::nLength, &eventsRead);
	int err = GetLastError();
	return inputRecord.Event.KeyEvent;
}