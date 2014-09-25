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
	FlushConsoleInputBuffer(hConsole);
	return 1;
}

KEY_EVENT_RECORD InputClass::GetKeypress()
{
	DWORD eventsRead;

	GetNumberOfConsoleInputEvents(hConsole, &eventsToRead);

	if (eventsToRead >= 1)
	{
		ReadConsoleInput(hConsole, &inputRecord, nLength, &eventsRead);
		if (inputRecord.Event.KeyEvent.bKeyDown == true)
			prevKeyEventRecord = inputRecord.Event.KeyEvent;
	}
	Sleep(75);
	return inputRecord.Event.KeyEvent;
}

KEY_EVENT_RECORD InputClass::GetKeypressWait()
{
	DWORD eventsRead;

	ReadConsoleInput(hConsole, &inputRecord, nLength, &eventsRead);
	return inputRecord.Event.KeyEvent;
}