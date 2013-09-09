#include "stdafx.h"
#include "CMusic.h"


CMusic::CMusic() : CResourceDirectories()
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
}


CMusic::~CMusic()
{
	Mix_HaltMusic();
	for (stringVector::iterator itr = m_musicNames.begin(); itr != m_musicNames.end(); ++itr)
	{
		// (*itr) is the string inside of the vector at each given point
		Mix_FreeMusic(getMusic(*itr));
	}

	for (stringVector::iterator itr = m_chunkNames.begin(); itr != m_chunkNames.end(); ++itr)
	{
		Mix_HaltChannel(getChanel(*itr));
		Mix_FreeChunk(getChunk(*itr));
	}

	Mix_CloseAudio();
	Mix_Quit();
}


Mix_Music* CMusic::getMusic(std::string fileName)
{
	musicMap::const_iterator itr = m_music.find(fileName);
	if (itr == m_music.end())
	{
#ifdef DEBUG
		assert(false);
#endif // DEBUG
	}
	else
	{
		return itr->second;
	}
}


Mix_Chunk* CMusic::getChunk(std::string fileName)
{
	chunkMap::const_iterator itr = m_chunks.find(fileName);
	if (itr == m_chunks.end())
	{
#ifdef DEBUG
		assert(false);
#endif // DEBUG
	}
	else
	{
		return itr->second;
	}
}


int CMusic::getChanel(std::string fileName)
{
	chanelMap::const_iterator itr = m_chanels.find(fileName);
	if (itr == m_chanels.end())
	{
#ifdef DEBUG
		assert(false);
#endif // DEBUG
	}
	else
	{
		return itr->second;
	}
}


void CMusic::load_music(std::string fileName)
{
	// "can load WAVE, MOD, MIDI, OGG, MP3, FLAC, and any file that you use a command to play with"
	// http://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_55.html

	std::string filePath = m_resource_music + fileName;
	Mix_Music* pMusic = Mix_LoadMUS(filePath.c_str());

	m_music.insert(musicMap::value_type(fileName, pMusic));
	m_musicNames.push_back(fileName);
}


void CMusic::play_music(std::string fileName, int loops)
{
	if (Mix_PlayingMusic() == 0) // music is not playing
	{
		Mix_PlayMusic(getMusic(fileName), loops);
		//Mix_HookMusicFinished(musicOver);
	}
}


void CMusic::stop_music()
{
	// do not need a reference to the music playing because there can only be one 'music' playing
	Mix_HaltMusic();
}


void CMusic::load_chunk(std::string fileName)
{
	// "The name is misleading. It also supports OGG, MP3, MOD and MIDI"
	// http://sdl.beuc.net/sdl.wiki/Mix_LoadWAV

	std::string filePath = m_resource_music + fileName;
	Mix_Chunk* pChunck = Mix_LoadWAV(filePath.c_str());
#ifdef DEBUG
	assert(pChunck != NULL);
#endif // DEBUG

	m_chunks.insert(chunkMap::value_type(fileName, pChunck));
	m_chunkNames.push_back(fileName);
}


void CMusic::play_chunk(std::string fileName, int loops, int chanel)
{
	int chanelReturn = Mix_PlayChannel(chanel, getChunk(fileName), loops);
#ifdef DEBUG
	assert(chanelReturn != -1);
#endif // DEBUG

	m_chanels.insert(chanelMap::value_type(fileName, chanelReturn));
}


void CMusic::stop_chunk(std::string fileName)
{
	Mix_HaltChannel(getChanel(fileName));
}


void CMusic::musicOver()
{
	// still have no idea how to solve this callback scope thing
}