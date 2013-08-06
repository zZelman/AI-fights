#include "stdafx.h"

#include "CRoom_1x2.h"


CRoom_1x2::CRoom_1x2(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
					 SCoords2<int> spawnCoords_screen,
					 std::string filePath, int imageWidth, int imageHeight,
					 int numImages_rows, int numImages_columns)

					 : CRoom(window, collisionMap, collisionRoom,
					 spawnCoords_screen,
					 filePath, imageWidth, imageHeight,
					 numImages_rows, numImages_columns)
{
	m_layout.setCoords(1, 2);
}

CRoom_1x2::~CRoom_1x2()
{
	CRoom::~CRoom();
}


void CRoom_1x2::update()
{
	// just to make sure that the first tick of time based things are not messy
	if (isFirstUpdate == true)
	{
		m_sAtributes.gravityTimer.start();
		isFirstUpdate = false;
	}

	if (!correctWindowCollision_down())
	{
		if (!correctRoomCollision_down())
		{
			if (!correctMapCollision_down())
			{
				m_topLeft.x += (int) m_sAtributes.velosity_x;
				m_topLeft.y += (int) m_sAtributes.velosity_y;

				setTopLeft(m_topLeft);

				isFalling = true;
			}
		}
	}

	// only update the adjacent room pointers when not falling
	if (!isFalling)
	{
		checkPtrs(1); // for now just 1 pixel
	}
	else // is falling - null pointers to prevent weird pathing glitches
	{
		nullPtrs();
	}
}


void CRoom_1x2::render()
{
	CRoom::render();
}


void CRoom_1x2::checkPtrs(int pixelCheck)
{
	nullPtrs();

	for (int i = 0; i < m_pRoomVector->size(); ++i)
	{
		CRoom* pRoom = m_pRoomVector->at(i);

		if (this->equals(pRoom))
		{
			continue;
		}

		// general logic:
		// if not found (false)
		//		then check to see if the room is found
		//		& set to true if found, false if not

		// [OPTIMIZATION]: have a better checking columns algorithm for 1x2 or 2x1 or 1x2 to exit checking early

		check_up(pRoom, pixelCheck);
		check_down(pRoom, pixelCheck);
		check_left(pRoom, pixelCheck);
		check_right(pRoom, pixelCheck);
	}
}


void CRoom_1x2::check_up(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_11_up == NULL || m_pRoom_21_up == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topLeft.x + m_width / 2;
		pointToCheck.y = m_topLeft.y - pixelCheck;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			// this is a 1x1 room, so all up's are the same, and should point to the same room
			m_pRoom_11_up = roomToCheck;
			m_pRoom_21_up = roomToCheck;
		}
	}
}


void CRoom_1x2::check_down(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_12_down == NULL || m_pRoom_22_down == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topLeft.x + m_width / 2;
		pointToCheck.y = m_bottomRight.y + pixelCheck;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			// this is a 1x1 room, so all down's are the same, and should point to the same room
			m_pRoom_12_down = roomToCheck;
			m_pRoom_22_down = roomToCheck;
		}
	}
}


void CRoom_1x2::check_left(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_11_left == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topLeft.x - pixelCheck;
		pointToCheck.y = m_topLeft.y + m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_11_left = roomToCheck;
		}
	}

	// null means not found
	if (m_pRoom_12_left == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_bottomLeft.x - pixelCheck;
		pointToCheck.y = m_bottomLeft.y - m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_12_left = roomToCheck;
		}
	}
}


void CRoom_1x2::check_right(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_21_right == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topRight.x + pixelCheck;
		pointToCheck.y = m_topRight.y + m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_21_right = roomToCheck;
		}
	}

	// null means not found
	if (m_pRoom_22_right == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_bottomRight.x + pixelCheck;
		pointToCheck.y = m_bottomRight.y - m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_22_right = roomToCheck;
		}
	}
}


SCoords2<int> CRoom_1x2::whichSubRoom(SCoords2<int>* pPoint)
{
	SCoords2<int> subRoom;
	int x = pPoint->x;
	int y = pPoint->y;

	// top left sub room (1,1)
	if (x >= m_topLeft.x && x <= (m_topLeft.x + m_width / 2) &&
		y >= m_topLeft.y && y <= (m_topLeft.y + m_height / 2))
	{
		subRoom.setCoords(1, 1);
		return subRoom;
	}

	// bottom left sub room (1,2)
	if (x >= m_bottomLeft.x && x <= (m_bottomLeft.x + m_width / 2) &&
		y >= (m_bottomLeft.y - m_height / 2) && y <= m_bottomLeft.y)
	{
		subRoom.setCoords(1, 2);
		return subRoom;
	}

	// something went wrong
#ifdef DEBUG
	assert(false);
#endif // DEBUG

	subRoom.setCoords(-1, -1);
	return subRoom;
}


bool CRoom_1x2::correctRoomCollision_down()
{
	for (int i = 0; i < m_pRoomVector->size(); ++i)
	{
		CRoom* pRoom = m_pRoomVector->at(i);

		if (this->equals(pRoom))
		{
			continue;
		}

		SCoords2<int> other_topLeft;
		SCoords2<int> other_topRight;
		SCoords2<int> other_bottomLeft;
		SCoords2<int> other_bottomRight;
		pRoom->getEverything(&other_topLeft, &other_topRight, &other_bottomLeft, &other_bottomRight);

		// Point collision detection extended from the midpoint on the bottom row
		SCoords2<int> midBottom;
		midBottom.setCoords(m_bottomLeft.x + m_width / 2, (int)(m_bottomLeft.y + m_sAtributes.velosity_y));
		if (pRoom->collision(&midBottom))
		{
			if (pRoom->getLayout()->x == 1)
			{
				setBottomRight(other_topRight.x, other_topRight.y);
			}
			else if (pRoom->getLayout()->x == 2)
			{
				SCoords2<int> subRoom = pRoom->whichSubRoom(&midBottom);

				if (subRoom.x == 1) // left side
				{
					setBottomLeft(other_topLeft.x, other_topLeft.y);
				}
				else if (subRoom.x == 2) // right side
				{
					setBottomRight(other_topRight.x, other_topRight.y);
				}
			}
			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
	}

	return false;
}


bool CRoom_1x2::correctMapCollision_down()
{
	// get the x coord in map space for a fast search
	int column = m_topLeft.x + m_sAtributes.velosity_x;
	int row = m_topLeft.y + m_sAtributes.velosity_y;
	m_pMap_collision->convertScreenToMap(&column, &row);

	const std::vector<STileData<int>*>* pMapTiles = m_pMap_collision->getMapTiles();
	for (int i = 0; i < pMapTiles->size(); ++i)
	{
		STileData<int>* pTile = pMapTiles->at(i);

		// we are only looking for a specific column (falling down), no need to search needlessly
		if (pTile->mapCoords.x != column)
		{
			continue;
		}

		SCoords2<int> midBottom;
		midBottom.setCoords(m_bottomLeft.x + m_width / 2, (int)(m_bottomLeft.y + m_sAtributes.velosity_y));
		if (pTile->collision(&midBottom))
		{
			setBottomRight(pTile->screenCoords_topLeft.x + pTile->width, pTile->screenCoords_topLeft.y);

			isFalling = false;
			m_sAtributes.gravityTimer.start();
			return true;
		}
	}

	return false;
}