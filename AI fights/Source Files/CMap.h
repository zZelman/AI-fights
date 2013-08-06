#ifndef CMAP_H
#define CMAP_H


#include "stdafx.h"
#include "CResourceDirectories.h"
#include "CSprite.h"
#include "CBot.h"
#include "SCoords2.h"

//////////////////////////////////////////////////////////////////////////
template<typename T> struct SCoords2;
//////////////////////////////////////////////////////////////////////////

// * used in representing each tile
// * saves on computation time at the cost of memory... worth it thought
//		does not have an innate AABB because AABB's are big, and there are a lot of tiles
//		instead has the data to produce an AABB
template<typename T>
struct STileData
{
	int width; // size of tile
	int height; // size of tile

	// LENGTH (column, row) number from the sprite sheet
	SCoords2<T> spriteCoords;

	// INDEX (column, row) representation for data structure axis
	SCoords2<T> mapCoords;

	// INDEX (x, y) representation for rendering
	SCoords2<T> screenCoords_topLeft;

	// INDEX (x, y) representation for rendering
	SCoords2<T> screenCoords_bottomRight;

	STileData();

	// returns true if the point is within the tile
	bool collision(SCoords2<T>* pPoint);
};


template<typename T>
STileData<T>::STileData() {}


template<typename T>
bool STileData<T>::collision(SCoords2<T>* pPoint)
{
	T x = pPoint->x;
	T y = pPoint->y;

	if (x >= screenCoords_topLeft.x && x <= screenCoords_bottomRight.x &&
	        y >= screenCoords_topLeft.y && y <= screenCoords_bottomRight.y)
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////


class CMap : public CResourceDirectories
{
public:
	CMap(CWindow* window, std::string fileName);
	~CMap();

	int getRows();
	int getColumns();

	int getWidth_tile();
	int getHeight_tile();

	const std::vector<STileData<int>*>* getMapTiles();

	// determines if the map is just drawn to the screen or if
	//		100% of the map is drawn just changed to fit the screen stretched
	void swapIsStretched();

	void load(); // loads a map file named 'fileName'
	void render(); // draws the loaded file

	// * checks if screen coords (x, y) are inside of any tiles in the map
	// * true if yes, false if now
	// * tileCollidedWith will be the returned tile that the aabb collided with
	//		this allows resolution of what to do next to happen outside of CMap
	bool collision_screenToMap(CAABB_f* aabb, CAABB_f* tileCollidedWith = NULL);

	// * checks if screen coords (x, y) are inside of any tiles in the map
	// * true if yes, false if now
	bool collision_screenToMap(SCoords2<int>* pPoint);

	// * checks if any part of the AABB is within a tile
	// * 0's represent no rendering -> non-zero is collision
	bool collision_mapToMap(int x, int y);

	// converts an (x,y) screen into an (column, row) map
	void convertScreenToMap(int* screenX, int* screenY);
	int convertScreenToMap_X(int screenX);
	int convertScreenToMap_Y(int screenY);

private:
	CWindow* m_pWindow;

	std::string m_tileSetName;	// tile set used to draw tiles

	int m_tileWidth;			// width of tiles
	int m_tileHeight;			// height of tiles

	int m_MapColumns;			// LENGTH number of tiles per row
	int m_MapRows;				// LENGTH number of tiles per column

	CSprite* m_pSpriteSheet;
	SCoords2<int>* m_pTileCoordsArray; // LENGTH an array of (row,col) coords on the sprite sheet for rendering
	int m_tileLength; // what image @ 'Length' on the sprite sheet is being rendered

	//std::vector<std::vector<int>> m_mapData; // a 2D vector of int's

	// every tile that exists (non 0 entry) for this map, is within this vector
	std::vector<STileData<int>*> m_pMapTiles;

	bool isMapLoaded;
	bool isMapStretched;

	// returns the value of a pure number ie: "123" and stops at the first invalade char "123.4" == "123"
	int stringToInt(std::string str);

	// a boolean to determine whether or not the tile is within screen viable space
	// the row/column are the INDECIES within the data structure holding the map
	// only works if isMapStretched == false
	bool shouldCull(int column, int row);

	void free();
};


#endif // !CMAP_H