#include "stdafx.h"
#include "CMusic.h"


CMusic::CMusic(std::string fileName) : CResourceDirectories()
{
	audio_rate		= 22050;
	audio_format	= AUDIO_S16; /* 16-bit stereo */
	audio_channels	= 2;
	audio_buffers	= 4096;

	int musicInitCode = Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
#ifdef DEBUG
	assert(musicInitCode >= 0);
#endif // DEBUG

	// after this call the vars will reflect what is actually set up, not just what you wanted
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	std::string filePath = m_resource_music += (fileName);
	m_pMusic = Mix_LoadMUS(filePath.c_str());
}


CMusic::~CMusic()
{
	Mix_HaltMusic();
	Mix_FreeMusic(m_pMusic);
	m_pMusic = NULL;
}


void CMusic::play()
{
	Mix_PlayMusic(m_pMusic, 0);
	//Mix_HookMusicFinished(musicOver);
}


void CMusic::musicOver()
{
	Mix_HaltMusic();
	Mix_FreeMusic(m_pMusic);
	m_pMusic = NULL;
}