#pragma once

#include "stdafx.h"
#include "CResourceDirectories.h"
#include "CSprite.h"
#include "CBot.h"
#include "Math2D.h"

//////////////////////////////////////////////////////////////////////////

struct SCoords2i;
class CAABB_f;

//////////////////////////////////////////////////////////////////////////

class CMap : public CResourceDirectories
{
public:
	CMap(CWindow* window, std::string fileName);
	~CMap();

	int getRows();
	int getColumns();

	void load(); // loads a map file named 'fileName'
	void render(); // draws the loaded file

	// * checks if screen coords (x, y) are inside of any tiles in the map
	// * true if yes, false if now
	// * tileCollidedWith will be the returned tile that the aabb collided with
	//		this allows resolution of what to do next to happen outside of CMap
	bool collision_screenToMap(CAABB_f* aabb, CAABB_f* tileCollidedWith = NULL);

	// * checks if any part of the AABB is within a tile
	// * 0's represent no rendering -> non-zero is collision
	bool collision_mapToMap(int x, int y);

private:
	CWindow* m_pWindow;

	std::string m_tileSetName;	// tile set used to draw tiles

	int m_tileWidth;			// width of tiles
	int m_tileHeight;			// height of tiles

	int m_MapColumns;			// number of tiles per row
	int m_MapRows;				// number of tiles per column

	CSprite* m_pSpriteSheet;
	SCoords2i* m_pTileCoordsArray; // LENGTH an array of (row,col) coords on the sprite sheet for rendering
	int m_tileLength; // what image @ 'Length' on the sprite sheet is being rendered

	std::vector<std::vector<int>> m_mapData; // a 2D vector of int's

	bool isMapLoaded;

	// returns the value of a pure number ie: "123" and stops at the first invalade char "123.4" == "123"
	int stringToInt(std::string str);

	void free();
};