#ifndef CAI_H
#define CAI_H

#include "stdafx.h"

#include "CUpdatable.h"

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

	virtual void update();

	// * this is the interface that controlls the movement of the AI
	// * local bools are set, and then update() exicutes on them with restrictions
	void setMove(bool up, bool down, bool left, bool right);

private:
	// movement bools set by AI generator through setMove
	bool isMovingUp, isMovingDown;
	bool isMovingLeft, isMovingRight;

	// specific movement control
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};



#endif // !CAI_H