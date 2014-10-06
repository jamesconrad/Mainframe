#include "audioclass.h"
#include <uuids.h>

AudioClass::AudioClass()
{
	pigb = NULL;
	pimc = NULL;
	pimex = NULL;
	piba = NULL;
	ready = false;
	currentFile = NULL;
}

AudioClass::~AudioClass()
{
	Shutdown();
}

void AudioClass::Shutdown()
{
	if (pimc)
		pimc->Stop();

	if (pigb)
	{
		pigb->Release();
		pigb = NULL;
	}

	if (pimc)
	{
		pimc->Release();
		pimc = NULL;
	}

	if (pimex)
	{
		pimex->Release();
		pimex = NULL;
	}

	if (piba)
	{
		piba->Release();
		piba = NULL;
	}

	ready = false;
}

bool AudioClass::Load(LPCWSTR szFile)
{
	if (currentFile != szFile)
	{
		Shutdown();
		CoInitialize(NULL);
		if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&this->pigb)))
		{
			pigb->QueryInterface(IID_IMediaControl, (void**)&pimc);
			pigb->QueryInterface(IID_IMediaEventEx, (void**)&pimex);
			pigb->QueryInterface(IID_IBasicAudio, (void**)&piba);

			HRESULT hr = pigb->RenderFile(szFile, NULL);
			if (SUCCEEDED(hr))
			{
				ready = true;
			}
		}
		return ready;
	}
	return ready;
}

bool AudioClass::Play()
{
	if (ready && pimc)
	{
		HRESULT hr = pimc->Run();
		return SUCCEEDED(hr);
	}
	return false;
}

bool AudioClass::Pause()
{
	if (ready && pimc)
	{
		HRESULT hr = pimc->Pause();
		return SUCCEEDED(hr);
	}
	return false;
}

bool AudioClass::Stop()
{
	if (ready && pimc)
	{
		HRESULT hr = pimc->Stop();
		return SUCCEEDED(hr);
	}
	return false;
}

bool AudioClass::SetVolume(long vol)
{
	if (ready && piba)
	{
		HRESULT hr = piba->put_Volume(vol);
		return SUCCEEDED(hr);
	}
	return false;
}

long AudioClass::GetVolume()
{
	if (ready && piba)
	{
		long vol = -1;
		HRESULT hr = piba->get_Volume(&vol);
		if (SUCCEEDED(hr))
			return vol;
	}

	return -1;
}