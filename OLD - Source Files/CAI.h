#ifndef CAI_H
#define CAI_H

#include "stdafx.h"

#include "CUpdatable.h"
#include "CRoom.h"

// * base class for all AI in the game
class CAI : public CUpdatable
{
public:
	// * window:						window to be drawn in
	// * collisionMap:					map representing tile collision for this room
	// * collisionRoom:				pointer to what container this room is apart of (outside of this object)
	// * spawnCoords_screen:	the (x,y) SCREEN SPACE of the top left of where this room will start at
	// * filePath:						full relative path ("Recource Files/...") to sprite representing room
	// * imageWidth:				width of sprite
	// * imageHeight:				height of sprite
	// * numImages_rows:			how many rows of images are there in the sprite to be loaded
	// * numImages_columns:	how many columns of images are there in the sprite to be loaded
	CAI(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
	    SCoords2<int> spawnCoords_screen,
	    std::string filePath, int imageWidth, int imageHeight,
	    int numImages_rows = 1, int numImages_columns = 1);
	CAI();
	~CAI();

	void setCurrentRoom(CRoom* pRoom);

	virtual void update();

	// * this is the interface that controlls the movement of the AI
	// * local bools are set, and then update() exicutes on them with restrictions
	void setMove(bool up, bool down, bool left, bool right);

protected:
	// movement bools set by AI generator through setMove
	bool isMovingUp, isMovingDown;
	bool isMovingLeft, isMovingRight;

	// the room that this AI currently resides within
	CRoom* m_pCurrentRoom;

	// * specific movement control
	// * true if collision, false if no collision
	virtual bool isCollision_up(SCoords2<int>* leftCorner, SCoords2<int>* rightCorner);
	virtual bool isCollision_down(SCoords2<int>* leftCorner, SCoords2<int>* rightCorner);
	virtual bool isCollision_left(SCoords2<int>* top, SCoords2<int>* bottom);
	virtual bool isCollision_right(SCoords2<int>* top, SCoords2<int>* bottom);

	// * while falling, will this AI's next step be inside a map tile?
	//		if true; step to the edge of the tile
	//		else, step normally
	// * stepping is based on m_sAtributes's velocities
	// * if return true, sets isFalling == false b/c falling means stepping normally
	virtual bool correctMapCollision_down();
};



#endif // !CAI_H