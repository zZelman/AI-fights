#pragma once

#include "stdafx.h"
#include "CResourceDirectories.h"

class CMusic : public CResourceDirectories
{
public:
	CMusic();
	~CMusic();

	Mix_Music* getMusic(std::string fileName); // returns the associated music pointer from the file name
	Mix_Chunk* getChunk(std::string fileName); // returns the associated chunk pointer from the file name
	int getChanel(std::string fileName); // returns the associated channel for a chunk that has started playing

	void play_music(std::string fileName, int loops); // start the music (-1 for infinet, 0 for 1 etc)
	void stop_music();

	void play_chunk(std::string fileName, int loops, int chanel = -1); // starts a sound clip
	void stop_chunk(std::string fileName);

	void load(std::string fileName); // loads any supported music file (chooses how to load by file extension)

private:
	Mix_Chunk* m_pChunck; // sound effects
	int m_chunkChanel;

	typedef std::vector<std::string> stringVector;

	typedef std::unordered_map<std::string, Mix_Music*> musicMap;
	musicMap m_music; // hashmap of all music files <string, Mix_Music*>
	stringVector m_musicNames; // all names of 'music' files that have been loaded

	typedef std::unordered_map<std::string, Mix_Chunk*> chunkMap;
	chunkMap m_chunks; // hashmap of all chunk files <string, Mix_Chunck*>
	stringVector m_chunkNames; // names of all 'chunk' files that have been loaded

	typedef std::unordered_map<std::string, int> chanelMap;
	chanelMap m_chanels; // hashmap of all chunk channels <string, int>

	int audio_rate;
	Uint16 audio_format; /* 16-bit stereo */
	int audio_channels;
	int audio_buffers;

	void musicOver(); // when music has stopped playing this gets called [TODO: fix callback scope]

	void load_ogg(std::string filePath); // all ogg files are treated as 'music' and not 'chunks'
	void load_wav(std::string filePath); // all wav files are treated as 'chunks' and not 'music'
	void load_mp3(std::string filePath);

};