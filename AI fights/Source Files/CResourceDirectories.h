#pragma once

#include "stdafx.h"

class CResourceDirectories
{
public:
	CResourceDirectories(); // just sets the directory paths as strings
	~CResourceDirectories();

protected:
	std::string m_resource_texture; // directory to texture files
	std::string m_resource_sprite; // directory to sprite files
	std::string m_resource_music; // directory to music files
	std::string m_resource_tileSets; // tilesets
};