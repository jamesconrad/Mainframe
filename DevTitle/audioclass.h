#ifndef AUDIOCLASS_H
#define AUDIOCLASS_H
//AudioClass Definition
#include <Windows.h>
#include <mmsystem.h>
#include <strmif.h>
#include <control.h>

//needed by AudioClass to play music
#pragma comment(lib, "strmiids.lib")

class AudioClass
{
public:
	AudioClass();
	AudioClass(const AudioClass&);
	~AudioClass();

	bool Load(LPCWSTR filename);
	void Shutdown();

	bool Play();
	bool Pause();
	bool Stop();

	//-10000 is lowest, 0 is highest
	bool SetVolume(long vol);
	long GetVolume();

private:
	IGraphBuilder* pigb;
	IMediaControl* pimc;
	IMediaEventEx* pimex;
	IBasicAudio* piba;
	LPCWSTR currentFile;
	bool ready;
};

#endif
