#ifndef CMUSIC_H
#define CMUSIC_H

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

	void load_music(std::string fileName);
	void play_music(std::string fileName, int loops); // start the music (-1 for infinet, 0 for 1 etc)
	void stop_music();

	void load_chunk(std::string fileName); // loads any supported music file (chooses how to load by file extension)
	void play_chunk(std::string fileName, int loops, int chanel = -1); // starts a sound clip
	void stop_chunk(std::string fileName);

private:

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

};



#endif // !CMUSIC_H
