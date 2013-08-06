#ifndef CROOM_1X2_H
#define CROOM_1X2_H


#include "stdafx.h"

#include "CRoom.h"

// * This class represents a 1u width by 1u height room
class CRoom_1x2 : public CRoom
{
public:
	CRoom_1x2(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
		SCoords2<int> spawnCoords_screen,
		std::string filePath, int imageWidth, int imageHeight,
		int numImages_rows = 1, int numImages_columns = 1);
	~CRoom_1x2();

	void update();
	void render();

protected:
	void checkPtrs(int pixelCheck);
	void check_up(CRoom* roomToCheck, int pixelCheck);
	void check_down(CRoom* roomToCheck, int pixelCheck);
	void check_left(CRoom* roomToCheck, int pixelCheck);
	void check_right(CRoom* roomToCheck, int pixelCheck);

	SCoords2<int> whichSubRoom(SCoords2<int>* pPoint);

	bool correctRoomCollision_down();
	bool correctMapCollision_down();
};



#endif // !CROOM_1X2_H