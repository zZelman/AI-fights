#pragma once

#include "stdafx.h"
#include "CResourceDirectories.h"

class CMap : public CResourceDirectories
{
public:
	CMap();
	~CMap();

	void load(std::string fileName); // loads a map file named 'fileName'
	void draw(); // draws the loaded file

private:
	int m_width;				// number of tiles per row
	int m_height;				// number of tiles per column

	int m_tileWidth;			// width of tiles
	int m_tileHeight;			// height of tiles

	std::string m_tileSetName;	// tileset used to draw tiles

	std::vector<std::vector<int>> m_mapData; // a 2D vector of int's

	// returns the value of a pure number ie: "123" and stops at the first invalade char "123.4" == "123"
	int stringToInt(std::string str);
};