#include "stdafx.h"
#include "CMusic.h"


CMusic::CMusic() : CResourceDirectories()
{
	m_chunkChanel = -1;

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


void CMusic::play_music(std::string fileName, int loops)
{
	Mix_PlayMusic(getMusic(fileName), loops);
	//Mix_HookMusicFinished(musicOver);
}


void CMusic::stop_music()
{
	// do not need a reference to the music playing because there can only be one 'music' playing
	Mix_HaltMusic();
}


void CMusic::play_chunk(std::string fileName, int loops, int chanel)
{
	int chanelReturn = Mix_PlayChannel(chanel, getChunk(fileName), loops);
	m_chanels.insert(chanelMap::value_type(fileName, chanelReturn));
}


void CMusic::stop_chunk(std::string fileName)
{
	Mix_HaltChannel(m_chunkChanel);
}


void CMusic::load(std::string fileName)
{
	std::string type_ogg = ".ogg";
	std::string type_wav = ".wav";
	std::string type_mp3 = ".mp3";

	// extract the extension from the fileName
	std::string extention = "";
	for (std::string::iterator itr = fileName.end()-4; itr != fileName.end(); ++itr)
	{
		extention.operator+=(*itr);
	}

	if (extention.compare(type_ogg) == 0)
	{
		load_ogg(fileName);
		return; // music file can only be one type
	}

	if (extention.compare(type_wav) == 0)
	{
		load_wav(fileName);
		return;
	}

	if (extention.compare(type_mp3) == 0)
	{
		load_mp3(fileName);
		return;
	}
}


void CMusic::musicOver()
{
	// still have no idea how to solve this callback scope thing
}


void CMusic::load_ogg(std::string fileName)
{
	std::string filePath = m_resource_music += (fileName);
	Mix_Music* pMusic = Mix_LoadMUS(filePath.c_str());

	m_music.insert(musicMap::value_type(fileName, pMusic));
	m_musicNames.push_back(fileName);
}


void CMusic::load_wav(std::string fileName)
{
	std::string filePath = m_resource_music += (fileName);
	Mix_Chunk* pChunck = Mix_LoadWAV(filePath.c_str());

	m_chunks.insert(chunkMap::value_type(fileName, pChunck));
	m_chunkNames.push_back(fileName);
}


void CMusic::load_mp3(std::string fileName)
{
	std::string filePath = m_resource_music += (fileName);
	assert(false);
}