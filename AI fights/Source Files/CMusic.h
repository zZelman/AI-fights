#pragma once

#include "stdafx.h"
#include "CResourceDirectories.h"

class CMusic : public CResourceDirectories
{
public:
	CMusic(std::string fileName);
	~CMusic();

	void play(); // start the music

private:
	Mix_Music* m_pMusic; // background music

	int audio_rate;
	Uint16 audio_format; /* 16-bit stereo */
	int audio_channels;
	int audio_buffers;

	void musicOver(); // when music has stopped playing this gets called
};