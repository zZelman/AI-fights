#ifndef CUPDATABLE_H
#define CUPDATABLE_H


#include "stdafx.h"
#include "CWindow.h"
#include "CMap.h"

//////////////////////////////////////////////////////////////////////////
class CRoom; // a prototype and not an #include because if #include, it would be circular inclusion
//////////////////////////////////////////////////////////////////////////

class CUpdatable
{
public:
	// if this has reached end conditions, this turns true
	bool isToBeDeleted;

	// holds all physics information
	SAtributes<float> m_sAtributes;

	// * window:						window to be drawn in
	// * collisionMap:					map representing tile collision for this
	// * collisionRoom:				pointer to the rooms that this can collide with
	// * spawnCoords_screen:	the (x,y) SCREEN SPACE of the TOP LEFT of where this will start at
	// * filePath:						full relative path ("Recource Files/...") to sprite representing room
	// * imageWidth:				width of sprite
	// * imageHeight:				height of sprite
	// * numImages_rows:			how many rows of images are there in the sprite to be loaded
	// * numImages_columns:	how many columns of images are there in the sprite to be loaded
	CUpdatable(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
	           SCoords2<int> spawnCoords_screen,
	           std::string filePath, int imageWidth, int imageHeight,
	           int numImages_rows = 1, int numImages_columns = 1);
	CUpdatable();
	~CUpdatable();

	// SCREEN SPACE resets the values within the GIVEN 4 coord pairs to match what this rooms currently are
	void getEverything(SCoords2<int>* pTopLeft, SCoords2<int>* pTopRight,
	                   SCoords2<int>* pBottomLeft, SCoords2<int>* pBottomRight);

	// SCREEN SPACE resets the values within the GIVEN coord pairs to what this room currently are
	void getMinMax(SCoords2<int>* pTopLeft, SCoords2<int>* pBottomRight);

	// distance between each respective coord sets
	int getWidth();
	int getHeight();

	// calculates NEW width and height based on the coords given
	void setEverything(SCoords2<int> topLeft, SCoords2<int> topRight,
	                   SCoords2<int> bottomLeft, SCoords2<int> bottomRight);

	// calculates other coords based on set widths and heights
	void setTopLeft(SCoords2<int> topLeft);
	void setTopLeft(int x, int y);

	// calculates other coords based on set widths and heights
	void setTopRight(SCoords2<int> topRight);
	void setTopRight(int x, int y);

	// calculates other coords based on set widths and heights
	void setBottomLeft(SCoords2<int> bottomLeft);
	void setBottomLeft(int x, int y);

	// calculates other coords based on set widths and heights
	void setBottomRight(SCoords2<int> bottomRight);
	void setBottomRight(int x, int y);

	// checks if the point in SCREEN space is within this's edges
	bool collision(SCoords2<int>* pPoint);

	virtual void update();
	void render();

protected:
	// the room that this collides with
	std::vector<CRoom*>* m_pRoom_collision;

	// a bool to the first tick of time dependent things (ie: gravity) not messy the first time through
	bool isFirstUpdate;

	// window everything will be rendered to
	CWindow* m_pWindow;

	// the map that this room will be collision detected against
	CMap* m_pMap_collision;

	// the sprite image that will be used for the room
	CSprite* m_pSprite;

	// detentions from one corner to another
	int m_width;
	int m_height;

	// 4 corners of the box, in screen space
	SCoords2<int> m_topLeft;
	SCoords2<int> m_topRight;
	SCoords2<int> m_bottomLeft;
	SCoords2<int> m_bottomRight;

	// * While falling, will the rooms next step be off of the collision map?
	//		if true, isToBeDeleted = true
	//		else, do nothing
	// * stepping is based on m_sAtributes's velocities
	void offCollisionMap();
};



#endif // !CUPDATABLE_H
