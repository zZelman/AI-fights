#include "stdafx.h"
#include "CUpdatable.h"

#ifndef CROOM_H
#define CROOM_H

// * Base class for all Rooms
// * NOTE: all virtual functions are intended to be overridden, their inate functionality is intended for a 1x1 room
class CRoom : public CUpdatable
{
public:
	// * Pointers to the room(s) to the respective directions [11 = sub room (1,1), etc]
	// * NULL if there is no room
	CRoom* m_pRoom_11_up;
	CRoom* m_pRoom_11_left;

	CRoom* m_pRoom_21_up;
	CRoom* m_pRoom_21_right;

	CRoom* m_pRoom_12_left;
	CRoom* m_pRoom_12_down;

	CRoom* m_pRoom_22_right;
	CRoom* m_pRoom_22_down;


	// * window:						window to be drawn in
	// * collisionMap:					map representing tile collision for this room
	// * collisionRoom:				pointer to what container this room is apart of (outside of this object)
	// * spawnCoords_screen:	the (x,y) SCREEN SPACE of the top left of where this room will start at
	// * filePath:						full relative path ("Recource Files/...") to sprite representing room
	// * imageWidth:				width of sprite
	// * imageHeight:				height of sprite
	// * numImages_rows:			how many rows of images are there in the sprite to be loaded
	// * numImages_columns:	how many columns of images are there in the sprite to be loaded
	CRoom(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
	      SCoords2<int> spawnCoords_screen,
	      std::string filePath, int imageWidth, int imageHeight,
	      int numImages_rows = 1, int numImages_columns = 1);
	CRoom();
	virtual ~CRoom();

	// returns what MAP Space column this room is in (topLeft)
	int getColumn();

	// returns what internal structure this room has [1x1, 1x2, 2x1, 2x2]
	// (column, row)
	const SCoords2<int>* getLayout();

	// checks equivalence by checking coords
	bool equals(CRoom* other);
	bool equals(int mapColumn);

	// * returns which sub room the point is in, in this room
	// * LENGTH: (1,1) is top left, (1,2) is top right and so on
	// * NON 1x1 rooms need to override this
	virtual SCoords2<int> whichSubRoom(SCoords2<int>* pPoint);

	virtual void update();

protected:
	// * whether or not this tile is descending
	// * set to false by correctRoomCollision_down == true or correctMapCollision_down == true
	//		b/c falling means stepping normally
	bool isFalling;

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

	// sets adjacent room pointers to NULL
	void nullPtrs();

	// * check if this room has neighbors
	// * NULL if no
	// * ONLY GETS CALLED WHEN isFallign == false
	// * 'roomToCheck' is the room in the data structure to check if it is adjacent
	// * 'pixelCheck' is how far in screen space coords to check for a room
	virtual void checkPtrs(int pixelCheck); // wrapper function for all pointer checks
	virtual void check_up(CRoom* roomToCheck, int pixelCheck);
	virtual void check_down(CRoom* roomToCheck, int pixelCheck);
	virtual void check_left(CRoom* roomToCheck, int pixelCheck);
	virtual void check_right(CRoom* roomToCheck, int pixelCheck);

	// * Checks collision in the area bounded by the given SCREEN space coords
	// * NOTE: if step of 'this' is too large, it will completely fall over 'other'
	// * 'this' is the coord set that DOES the stepping
	//bool collision(SCoords2<int>* pTopLeft_this, SCoords2<int>* pTopRight_this,
	//               SCoords2<int>* pBottomLeft_this, SCoords2<int>* pBottomRight_this,

	//               SCoords2<int>* pTopLeft_other, SCoords2<int>* pTopRight_other,
	//               SCoords2<int>* pBottomLeft_other, SCoords2<int>* pBottomRight_other);


	// * while falling, will this room's next step be inside another room?
	//		if true, step to the edge of the room
	//		else, step normally
	// * stepping is based on m_sAtributes's velocities
	// * if return true, sets isFalling == false b/c falling means steping normally
	virtual bool correctRoomCollision_down();

	// * while falling, will this room's next step be inside a map tile?
	//		if true; step to the edge of the tile
	//		else, step normally
	// * stepping is based on m_sAtributes's velocities
	// * if return true, sets isFalling == false b/c falling means stepping normally
	virtual bool correctMapCollision_down();
};


#endif // !CROOM_H