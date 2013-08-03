#pragma once

#include "stdafx.h"

class CRoom
{
public:
	CRoom(	CWindow* window, CMap* collisionMap, std::string fileName,
			SCoords2<int> spawnCoords,
			int imageWidth, int imageHeight,
			int numImages_rows = 1, int numImages_columns = 1);
	virtual ~CRoom();

	virtual void update();
	virtual void render();

protected:
	// window everything will be rendered to
	CWindow* m_pWindow;

	// the map that this room will be collision detected against
	CMap* m_pCollisionMap;

	// the sprite image that will be used for the room
	CSprite* m_pSprite;

	// holds all physics information for the room
	SAtributes<float> m_sAtributes;

	// * whether or not this tile is descending
	// * set to false by correctRoomCollision_down == true or correctMapCollision_down == true
	//		b/c falling means stepping normally
	bool isFalling;

	// 4 corners of the box, in screen space
	SCoords2<int> m_topLeft;
	SCoords2<int> m_topRight;
	SCoords2<int> m_bottomLeft;
	SCoords2<int> m_bottomRight;

	// * the current coords of this room within the collisionMap data structure
	// * INDEX
	SCoords2<int> m_coords;

	// * how big each respective wall is
	// * defines an interior box within the room for the AI to move around
	int m_wallSize_up;
	int m_wallSize_down;
	int m_wallSize_right;
	int m_wallSize_left;

	// * (x,y): 1x1, 1x2, 2x1, 2x2
	// * how many tiles the room takes up
	SCoords2<int> m_layout;

	// * If the room spans multiple tiles, it may have internal floors
	// * minimum value of 1
	int m_numInternalFloors;

	// * number of doors in this room
	// * max 2 (left right)
	int m_numDoors;

	// * true if there is a door on the respective side && numDoors > 0
	bool isDoorRight;
	bool isDoorLeft;

	// number of 'door ways' of ladders if there is a ladder
	int m_numLadderEnters;
	bool isLadder; // does room have a ladder in it

	// number of 'door ways' of stairs if there are stairs
	int m_numStairEnters;
	bool isStairs; // does room have stairs in it

	// * Pointers to the room(s) to the respective directions
	// * NULL if there is no room
	CRoom* m_pRoomUp;
	CRoom* m_pRoomDown;
	CRoom* m_pRoomLeft;
	CRoom* m_pRoomRight;

	// * check if this room has neighbors
	// * NULL if no
	// * ONLY GETS CALLED WHEN isFallign == false
	// * 'oldPtr' is this room's respective pointer
	void check_up(CMap* oldPtr);
	void check_down(CMap* oldPtr);
	void check_left(CMap* oldPtr);
	void check_right(CMap* oldPtr);

	// * while falling, will this room's next step be inside another room?
	//		if true, step to the edge of the room
	//		else, step normally
	// * stepping is based on m_sAtributes's velocities
	// * if return true, sets isFalling == false b/c falling means steping normally
	bool correctRoomCollision_down();

	// * while falling, will this room's next step be inside a map tile?
	//		if true; step to the edge of the tile
	//		else, step normally
	// * stepping is based on m_sAtributes's velocities
	// * if return true, sets isFalling == false b/c falling means stepping normally
	bool correctMapCollision_down();
};